#!/bin/sh
openssl dgst -sha256 -verify public.pem -signature "$2" "$1" 