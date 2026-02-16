# Installation Instructions for Smart Backup Utility

## Prerequisites
- GTK3 - Ensure you have GTK3 installed on your system. You can usually install it via your package manager.
- CMake - Ensure CMake is installed. You can download it from [CMake's official site](https://cmake.org/download/).

## Step-by-Step Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/bibek-17-git/0714-02-CSE-2100.git
   cd 0714-02-CSE-2100
   ```
2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```
3. Run CMake to configure the project:
   ```bash
   cmake ..
   ```
4. Compile the project:
   ```bash
   make
   ```
5. Install the Smart Backup Utility (optional):
   ```bash
   sudo make install
   ```

## Troubleshooting
- If you encounter issues with GTK3:
  - Ensure you have the latest version of GTK3 installed.
  - Check your environment variables to ensure they point to the GTK3 libraries.

- If CMake fails:
  - Make sure CMake is properly installed.
  - Verify that all dependencies are met.

## Verification Instructions
To verify the installation, you can run:
```bash
smart-backup-utility --version
```
If the installation was successful, you should see the version number of the utility.
