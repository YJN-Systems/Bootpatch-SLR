# Bootpatch-SLR

Bootpatch-SLR is the Linux kernel implementation of Selfpatch-SLR. It brings the Selfpatch-SLR structure layout randomization system into the Linux kernel, allowing structure layouts to be randomized during the boot process. For background information, documentation, and toolchain setup instructions, see the Selfpatch-SLR project:

- Documentation: https://spslr.yjn-systems.com
- Repository: https://github.com/YJN-Systems/Selfpatch-SLR

The implementation shares most of its code and design with Selfpatch-SLR and can be viewed as the kernel-specific variant of the project.

> **Status:** Research prototype  
> **Kernel base:** Linux 7.2-rc3  
> **Architecture support:** x86_64 only  
> **Production readiness:** Not production ready  

## Building

### Prerequisites

Bootpatch-SLR requires the custom `gcc-spslr` toolchain.

Instructions for building the toolchain are available in the [Selfpatch-SLR repository README](https://github.com/YJN-Systems/Selfpatch-SLR/blob/main/README.md).

### Kernel Configuration

The current baseline configuration used for testing is:

```bash
make defconfig

scripts/config --enable SPSLR
scripts/config --enable SANEMAKER
scripts/config --enable SAMPLES
scripts/config --enable SAMPLES_SPSLR
scripts/config --enable SAMPLE_SPSLR_TASKLIST

make olddefconfig
```

### Building the Kernel

After configuring the kernel and installing the `gcc-spslr` toolchain:

```bash
make CC=gcc-spslr CXX=g++-spslr scripts/gcc-plugins/ -j$(nproc)
make CC=gcc-spslr -j$(nproc)
```

