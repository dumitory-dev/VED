### Purpose

An application for creating and working with virtual encrypted logical drives.

### Functionality
1. Creates a crypted disk stored in a file (the path to the file and name, password, size of the created disk are indicated)
2. Mounts the specified file as a logical drive. (checking the password specified at creation)
3. Removes the previously mounted disk.
4. Provides the ability to view a list of mounted drives.
5. Encrypts / decrypts data written / read from disk.
6. Supports working with file paths in different languages.

### Technology Requirements
1. The GUI can be written in C # or Qt or another framework.
2. For development, use Visual Studio 2015.
3. To write a work plan, use MS Project Manager 2007 and higher.
4. Use GIT (gitlab.com) to store the source code.

### Implementation Details
1. User Interface
    - Functionality:
        - Create a disk (indicating the path to the file, password, disk size)
        - Mount the drive (with the path to the file and password verification)
        - dismount the specified drive
        - View the list of mounted disks (drive letter, size, file path)
        
           Implement the interface using a console application or GUI.
2. Driver - a virtual disk driver that redirects data to a file with encryption.
