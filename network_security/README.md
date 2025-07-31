# Network Security

This module implements network security features for TUNOS. All implementation and configuration is in English and contains no comments.

## Network Security Mechanisms

### VPN Engine
Implements a kernel-level VPN engine. All outgoing and incoming network traffic is routed through the VPN interface (vpn0). The kernel enforces strict packet handling and device binding.

### Network Tunneling
Implements a system-wide tunnel interface (tun0). All network packets can be redirected through this tunnel for additional privacy and security.

### DNS Resolver and Firewall
A local DNS resolver is enabled by default. All DNS queries are filtered through a firewall and blocklist to prevent leaks and access to malicious domains.

### MAC Address Randomization
MAC addresses are randomized per network connection to prevent device tracking.

### IP Leak Protection
IP leak protection is enabled. IPv6 is disabled by default to minimize leak risk.

### Wireless Policy Enforcement
Automatic disabling of Wi-Fi and Bluetooth when not in use. Wireless policies are enforced at the kernel level.

### VPN Protocol Support
IKEv2, OpenVPN, and WireGuard are supported and enabled through kernel configuration. All VPN protocols are managed by the kernel VPN engine.