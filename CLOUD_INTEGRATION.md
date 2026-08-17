# tess-tools in the CloudMR Cloud Backend

This document explains how `tess-tools` is consumed by the TESS cloud backend, the
API surface that backend depends on, and **two packaging problems in this
repository that currently break a clean install**.

No code in this repository was changed. This is a description of what was found
while building the cloud deployment, plus the fixes needed here.

Companion document: `TESS-app/ARCHITECTURE.md`.

---

## 1. How this package is consumed

`tess-tools` builds the Python package **`tess`** (currently `2.0.0.8`). It is a
`scikit-build` project: CMake compiles `CpTemperature` into a native binary at
`tess/bin/cpptemperature`, which the Python layer shells out to.

That has one important consequence for containers: a **C++ toolchain is required
to install this package, but not to run it.** The TESS image therefore installs
`build-essential cmake ninja-build git`, uses them, and purges them in the same
Docker layer — while explicitly keeping `libstdc++6` and `libgomp1`, because
`apt-get purge --auto-remove build-essential` will otherwise strip the C++
runtime the compiled solver needs.

```text
TESS-app/calculation/src/DockerfileFargate
    python:3.11-slim
      + build-essential cmake ninja-build git   (installed, used, purged)
      + libstdc++6 libgomp1                     (kept - runtime)
      + pip install -r requirements.txt         (brings cmtools -> pyable, pynico)
      + pip install --no-deps "tess @ git+.../tess-tools.git@${TESS_TOOLS_REF}"
```

Python must be **3.11**, not 3.12. `cmtools` carries a numpy constraint with no
3.12 wheels, so the image build fails there. `tess-tools` itself only requires
`>=3.10`.

---

## 2. Problem 1 — a clean `pip install` of this package fails today

`pyproject.toml` declares:

```toml
dependencies = [
  "pynico_eros_montin @ git+https://github.com/erosmontin/pynico.git",
  "pyable_eros_montin @ git+https://github.com/erosmontin/pyable.git",
]
```

Both git URLs are **unpinned**. `erosmontin/pyable` has since renamed its project
from `pyable_eros_montin` to `pyable`, and pip 23.1+ enforces name consistency for
direct URL requirements:

```text
WARNING: Generating metadata for package pyable_eros_montin produced metadata
         for project name pyable. Fix your #egg=pyable_eros_montin fragments.
Discarding git+https://github.com/erosmontin/pyable.git: Requested pyable from
  ... (from tess @ git+https://github.com/cloudmrhub/tess-tools.git@main)
  has inconsistent name: expected 'pyable-eros-montin', but metadata has 'pyable'
ERROR: Could not find a version that satisfies the requirement
       pyable-eros-montin (unavailable) (from tess) (from versions: none)
ERROR: No matching distribution found for pyable-eros-montin (unavailable)
```

So this fails right now:

```bash
pip install git+https://github.com/cloudmrhub/tess-tools
```

Which also means the `Dockerfile` **in this repository** is broken, since it does
exactly that.

Declared project names, for reference:

| repo | declared name | status |
|---|---|---|
| `erosmontin/pyable` | `pyable` | renamed — this is the breakage |
| `erosmontin/pynico` | `pynico_eros_montin` | fine |
| `erosmontin/raider` | `raider_eros_montin` | fine |

### The fix (one line each)

Pin the refs, exactly as `cloudmr-tools@main` already does:

```toml
dependencies = [
  "pynico_eros_montin @ git+https://github.com/erosmontin/pynico.git@v2",
  "pyable_eros_montin @ git+https://github.com/erosmontin/pyable.git@v2",
]
```

`pyable@v2` still declares `pyable_eros_montin`, so the name matches and the
resolver is happy. This is precisely why `cmtools@main` installs cleanly while the
`cmtools@v2` **tag** does not — the tag left its own git deps unpinned and got
broken retroactively by the rename.

**The general lesson: a tag is only as pinned as its own transitive git URLs.**

### The current workaround

Until the above lands, the TESS image installs this package with `--no-deps`:

```dockerfile
python -m pip install -r requirements.txt          # cmtools@main -> pyable@v2, pynico@v2
python -m pip install --no-deps "tess @ git+.../tess-tools.git@${TESS_TOOLS_REF}"
```

`cmtools@main` pins `pyable`/`pynico` to `@v2`, so by the time `tess` is installed
both dependencies are already present under their expected names. This works, but
it is a workaround in a *downstream* repository compensating for a declaration
problem here.

---

## 3. Problem 2 — this repository has no tags

```text
$ git ls-remote --tags https://github.com/cloudmrhub/tess-tools.git
(nothing)

$ git ls-remote --heads https://github.com/cloudmrhub/tess-tools.git
refs/heads/main
refs/heads/speedup
```

So the cloud image is pinned to `TESS_TOOLS_REF: main` because there is nothing
else to pin to. Combined with §2, TESS image builds currently track a **moving
branch that carries a broken dependency declaration**.

Cutting a tag — after fixing §2 — closes both problems at once, and lets
`TESS_TOOLS_REF` name an immutable ref the way CAMRIE pins `camrie-tools`.

---

## 4. API surface the cloud backend depends on

`TESS-app/calculation/src/app.py` uses exactly this. Changing any of it is a
breaking change for the deployed backend.

```python
import tess.tess as tess

engine = tess.Tess()

engine.setSpace(path)                   # reference geometry
engine.setMask(path)                    # optional

engine.setMaterialDensityMap(path)
engine.setBloodPerfusionMap(path)
engine.setHeatCapacityMap(path)
engine.setThermalConductivityMap(path)
engine.setMetabolismHeatMap(path)
engine.setSARMap(path)
engine.setTOldMap(path)

engine.setParam("scaleSARfile", path)   # optional

engine.setHeatingTime(seconds)
engine.setAirParameters(dict)
engine.setBloodParameters(dict)

result = engine.getOutput()             # -> pyable Imaginable
result.resampleOnTargetImage(space)

tess.getdfltAir()                       # module-level defaults
tess.getdfltBlood()
```

`getOutput()` must keep returning something with `resampleOnTargetImage` and a
form `cmtools.cmaws.cmrOutput.addAble` accepts — i.e. a `pyable` `Imaginable`.

Observed defaults:

```python
getdfltAir()   -> {'capacity': 1006, 'density': 1.3, 'temperature': 296,
                   'metabolism': 1006, 'conductivity': 0.026, 'perfusion': 0}
getdfltBlood() -> {'capacity': 1057, 'density': 3600, 'temperature': 310}
```

The backend layers the job's `air`/`blood` values over these and **skips `null`**,
so a frontend can send `{"capacity": null, "temperature": 296}` to mean "override
temperature only". Note `getdfltAir()` returns more keys than a frontend typically
sends, which is why merging over the defaults matters rather than replacing them.

### Reference space

The cloud backend resamples every map onto one geometry — the `mask` if provided,
otherwise `materialDensity` — and ships the resampled inputs in the result ZIP
alongside the output so a suspicious run is diagnosable from the ZIP alone.

The bundled `testdata/Head` has **no mask**, so the packaged smoke path exercises
the `materialDensity`-as-space fallback.

---

## 5. Bundled testdata, and how it is used

```text
tess/testdata/Head/MaterialDensity.nii.gz
tess/testdata/Head/BloodPerfusion.nii.gz
tess/testdata/Head/HeatCapacity.nii.gz
tess/testdata/Head/ThermalConductivity.nii.gz
tess/testdata/Head/Metabolism.nii.gz
tess/testdata/Head/SAR.nii.gz
tess/testdata/Head/TOld.nii.gz
```

Because CMake installs this tree into the package, it is present **inside the
container image**. That is genuinely useful: the cloud smoke test ran with
`type: local` descriptors pointing at
`/usr/local/lib/python3.11/site-packages/tess/testdata/Head/*.nii.gz` and needed
no S3 upload at all.

Please keep `testdata/Head` installed as package data. The deployment leans on it
for verification.

For local runs, `TESS-app/calculation/src/local_test.py` resolves a relative
`local_path` such as `Head/SAR.nii.gz` against this directory automatically, which
keeps the event JSON portable between Windows and WSL.

Verified solve on this data:

```text
Nx=179 Ny=179 Nz=50  dx=dy=dz=0.005  dt=0.2  heatingtime=30
150 steps, converged   (~90 s on Fargate Spot including a cold 2 GB image pull)
```

---

## 6. Suggested improvements here

**1. Pin the git dependencies (§2).** Highest priority — a clean install is
broken without it, including this repo's own Dockerfile.

**2. Cut a tag (§3).** Lets downstream pin an immutable ref.

**3. Fix `[project.urls]`.** They currently point at `erosmontin/cmrawspy`:

```toml
"Homepage" = "https://github.com/erosmontin/cmrawspy"
"Bug Tracker" = "https://github.com/erosmontin/cmrawspy/issues"
```

Almost certainly a copy-paste leftover; should be `cloudmrhub/tess-tools`.

**4. Reconcile the two version numbers.** `pyproject.toml` says `2.0.0.8` while
`setup.py` says `1.0.0.3`. Only one can be right, and the mismatch makes the
version logged per job ambiguous.

**5. Do not print the solver's stdout as a single bytes blob.** The Python layer
currently emits the whole C++ run as one `b'...'` repr. In CloudWatch that becomes
one enormous log line containing every convergence step, which is hard to read and
awkward to grep. Decoding it and logging line by line — or logging only the header
plus the final step at INFO and the rest at DEBUG — would make cloud logs far more
usable.

**6. Consider exposing a `--threads` / OpenMP knob.** The image keeps `libgomp1`
on the assumption the solver may be OpenMP-linked, and the Batch job definition
sets `TESS_THREADS` to the task's vCPU count, but nothing currently consumes it.

---

## 7. Where this fits

```text
CloudMR Brain  ->  Step Functions  ->  RunJobLambda  ->  AWS Batch (Fargate Spot)
                                                             |
                                                    TESS-app/calculation/src/app.py
                                                             |
                                                    tess-tools  (this repo)
                                                      tess/bin/cpptemperature
```

`tess-tools` owns the science: the thermal solver and its Python wrapper.
`TESS-app` owns the cloud: descriptors, S3, packaging, Batch, IAM, CI.

The same split holds for CAMRIE, where `camrie-tools` owns the MRI pipeline and
`CAMRIE-app` owns the AWS wrapper. Keeping that boundary clean is what allows both
applications to share one deployment architecture while computing entirely
different things.
