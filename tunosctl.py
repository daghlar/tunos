import sys
import os
import argparse
import subprocess

RESOURCE_MAP = {
    'location': 'location_control/location_access',
    'sensor': 'sensor_control/sensor_access',
    'network': 'network_control/network_access',
    'storage': 'storage_control/storage_access',
    'contact': 'contact_control/contact_access',
    'camera': 'camera_control/camera_access',
    'microphone': 'microphone_control/microphone_access',
}

SYSFS_BASE = '/sys/kernel/'

def show(profile, app):
    for res, node in RESOURCE_MAP.items():
        path = os.path.join(SYSFS_BASE, node)
        try:
            with open(path, 'r') as f:
                lines = f.readlines()
                found = False
                for p, line in enumerate(lines):
                    if p == profile:
                        values = line.strip().split()
                        if app < len(values):
                            print(f'{res}: {values[app]}')
                            found = True
                if not found:
                    print(f'{res}: unavailable')
        except Exception as e:
            print(f'{res}: error ({e})')

def set_toggle(profile, app, resource, value):
    node = RESOURCE_MAP.get(resource)
    if not node:
        print('Unknown resource:', resource)
        return
    path = os.path.join(SYSFS_BASE, node)
    try:
        with open(path, 'w') as f:
            f.write(f'{profile} {app} {value}\n')
        print(f'Set {resource} for profile {profile}, app {app} to {value}')
    except Exception as e:
        print(f'Error setting {resource}: {e}')

def logs(tail=50):
    try:
        output = subprocess.check_output(['dmesg'], encoding='utf-8')
        lines = [l for l in output.split('\n') if 'PERM_DENY' in l]
        for line in lines[-tail:]:
            print(line)
    except Exception as e:
        print(f'Error reading logs: {e}')

def main():
    parser = argparse.ArgumentParser(description='TUNOS Privacy Admin Tool')
    subparsers = parser.add_subparsers(dest='cmd')

    show_parser = subparsers.add_parser('show')
    show_parser.add_argument('--profile', type=int, required=True)
    show_parser.add_argument('--app', type=int, required=True)

    set_parser = subparsers.add_parser('set')
    set_parser.add_argument('--profile', type=int, required=True)
    set_parser.add_argument('--app', type=int, required=True)
    set_parser.add_argument('--resource', type=str, required=True)
    set_parser.add_argument('--value', type=int, choices=[0,1], required=True)

    logs_parser = subparsers.add_parser('logs')
    logs_parser.add_argument('--tail', type=int, default=50)

    args = parser.parse_args()
    if args.cmd == 'show':
        show(args.profile, args.app)
    elif args.cmd == 'set':
        set_toggle(args.profile, args.app, args.resource, args.value)
    elif args.cmd == 'logs':
        logs(args.tail)
    else:
        parser.print_help()

if __name__ == '__main__':
    main()
