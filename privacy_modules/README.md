# Privacy Modules

This module provides system-wide privacy controls for TUNOS. All implementation and configuration is in English and contains no comments.

## Privacy Mechanisms

### Location Access Control
Provides a strict kernel-level toggle for enabling or disabling access to device location for all user-space processes. The state is exposed via sysfs and can be changed at runtime.

### Network Access Control
Provides a strict kernel-level toggle for enabling or disabling network access for all user-space processes. The state is exposed via sysfs and can be changed at runtime.

### Sensor Access Control
Provides a strict kernel-level toggle for enabling or disabling access to device sensors (camera, microphone, etc.) for all user-space processes. The state is exposed via sysfs and can be changed at runtime.

### DNS Privacy
Enables DNS-over-HTTPS, DNS-over-TLS, and DNSCrypt for all outgoing DNS queries. This prevents eavesdropping and manipulation by third parties.

### Network Firewall
Enforces a kernel-level firewall, blocking all unauthorized network connections and optionally blocking background network activity.

### Onion Routing Integration
Integrates Tor at the system level. All network traffic can be routed through Tor for maximum anonymity. Tor SOCKS and control ports are configurable.

### Tracker Blocklist
Maintains a system-level blocklist of known analytics and tracking domains. All outgoing requests to these domains are blocked at the kernel level.