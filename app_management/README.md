# Application Management

This module manages application sandboxing, permission control, signature verification, and alternative app store integration for TUNOS. All implementation and configuration is in English and contains no comments.

## App Management Mechanisms

### Isolated Storage
Each application receives a dedicated, isolated storage area in kernel memory. Applications cannot access storage belonging to other apps. Storage is allocated and deallocated dynamically.

### Permission Control
Permissions are managed at the kernel level. Each app has a 32-bit permission mask. Permissions can be set or checked for each app individually.

### Application Sandboxing
Each app runs in a strict sandbox. The kernel enforces user-space restrictions and prevents apps from accessing system resources outside their sandbox.

### Signature Verification
App binaries are verified using SHA-256 signatures before execution. The kernel checks the hash of the binary against the provided signature to ensure authenticity.

### Alternative App Store Integration
Aurora Store and F-Droid are enabled as alternative app sources. Detached signature verification is supported for secure app installation.

### MicroG Support
MicroG compatibility and signature spoofing are configurable at the system level.

### Telemetry-Free Applications
System telemetry is disabled by default. Only telemetry-free applications are permitted.

### Time and Location-Based Permissions
Permissions can be restricted based on time or location using kernel configuration files.