FROM python:3.12-slim

# Install system dependencies for building C++ extensions
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    ninja-build \
    git \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install the package
RUN pip install git+https://github.com/cloudmrhub/tess-tools
COPY tess/test.py .
# Create directories for matplotlib
RUN mkdir -p /tmp/matplotlib /root/.cache/matplotlib
ENV MPLCONFIGDIR=/root/.cache/matplotlib
# CMD ["python","test.py"]

