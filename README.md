# TUNOS (Trusted Unified Network Operating System)

TUNOS is an open-source, privacy and security-focused Android-based operating system. The project is structured in modular components, each responsible for a critical aspect of the system. Development follows a strict order, starting from the core system and progressing through privacy, application management, network security, updates, user interface, development infrastructure, device support, community, and corporate support.

## Main Modules (Development Order)
1. Kernel and System Level
2. Privacy Modules
3. Application Management
4. Network Security
5. Update Mechanism
6. User Interface & UX
7. Development Infrastructure
8. Supported Devices
9. Community & Documentation
10. Corporate Support & Funding

- All code and documentation will be in English.
- No comments will be present in any code files. 

## Privacy Controls (Sysfs Interface)

Each privacy-sensitive resource (location, sensor, network, storage, contact, camera, microphone) is controlled per-app and per-profile via sysfs nodes:

- `/sys/kernel/location_control/location_access`
- `/sys/kernel/sensor_control/sensor_access`
- `/sys/kernel/network_control/network_access`
- `/sys/kernel/storage_control/storage_access`
- `/sys/kernel/contact_control/contact_access`
- `/sys/kernel/camera_control/camera_access`
- `/sys/kernel/microphone_control/microphone_access`

**Write Format:**
```
echo "<profile_id> <app_id> <value>" > <node>
```
**Read Format:**
```
cat <node>
```
Returns a matrix of toggles for each profile and app.

## Permission IDs

| perm_id | Resource     |
|---------|--------------|
| 0       | location     |
| 1       | sensor       |
| 2       | network      |
| 3       | storage      |
| 4       | contact      |
| 5       | camera       |
| 6       | microphone   |

## Admin CLI Usage

`tunosctl.py` allows admins to manage privacy toggles and view logs:

Show all toggles for an app/profile:
```
python3 tunosctl.py show --profile 0 --app 1
```
Set a resource toggle:
```
python3 tunosctl.py set --profile 1 --app 2 --resource camera --value 0
```
View audit logs:
```
python3 tunosctl.py logs --tail 50
```

## Audit Logging

All denied accesses are logged in the kernel log (`dmesg`) with details:
```
PERM_DENY profile=<profile> app=<app> perm=<perm_id> reason=<reason>
```

## Sandboxing Policy

Each app runs with a unique UID/GID per profile, in its own Linux namespaces (user, mount, PID), chrooted to `/appsandbox`, and under a seccomp filter that blocks IPC and dangerous syscalls. Inter-app communication and privilege escalation are prevented by default.

## Testing and Validation

- Write/read all sysfs nodes for each resource and verify correct state changes
- Attempt resource access with toggles on/off and confirm allow/deny behavior
- Check audit logs for denied accesses
- Run test apps in the sandbox and attempt to bypass isolation or use restricted syscalls; confirm all are blocked
- Use `tunosctl.py` for management and validation