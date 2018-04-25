#!/bin/bash

pflag=false

usage="$(basename "$0") [-h] [-p <password>] 

where:
    -h  show this help
    -s  set the password for certificates"


while getopts ':hp:' option; do
  case "$option" in
    h) echo "$usage"
       exit
       ;;
    p) password=$OPTARG
       pflag=true
       ;;
    :) printf "missing argument for -%s\n" "$OPTARG" >&2
       echo "$usage" >&2
       exit 1
       ;;
    *) echo "Unimplemented option: -$OPTARG" >&2; exit 1;;
   \?) printf "illegal option: -%s\n" "$OPTARG" >&2
       echo "$usage" >&2
       exit 1
       ;;
  esac
done
shift $((OPTIND - 1))

if ! $pflag
then
    echo "-p <password> must be specified." >&2
    exit 1
fi

printf "Certificate password will be: [%s]\n\n" "$password" >&2

# Generate valid CA
openssl genrsa -passout pass:$password -des3 -out eftnode_cli_ca.key 4096
openssl req -passin pass:$password -new -x509 -days 365 -key eftnode_cli_ca.key -out eftnode_cli_ca.crt -subj "/C=AU/ST=NSW/L=Sydney/O=OpenEFT/OU=OpenEFT/CN=openeft-cli Root CA"

# Generate valid Server Key/Cert
openssl genrsa -passout pass:$password -des3 -out eftnode_cli_server.key 4096
openssl req -passin pass:$password -new -key eftnode_cli_server.key -out eftnode_cli_server.csr -subj "/C=AU/ST=NSW/L=Sydney/O=OpenEFT/OU=OpenEFT Node/CN=localhost"
openssl x509 -req -passin pass:$password -days 365 -in eftnode_cli_server.csr -CA eftnode_cli_ca.crt -CAkey eftnode_cli_ca.key -set_serial 01 -out eftnode_cli_server.crt

# Remove passphrase from the Server Key
openssl rsa -passin pass:$password -in eftnode_cli_server.key -out eftnode_cli_server.key

# Generate valid Client Key/Cert
openssl genrsa -passout pass:$password -des3 -out eftnode_cli_client.key 4096
openssl req -passin pass:$password -new -key eftnode_cli_client.key -out eftnode_cli_client.csr -subj "/C=AU/ST=NSW/L=Sydney/O=OpenEFT/OU=OpenEFT Client/CN=localhost"
openssl x509 -passin pass:$password -req -days 365 -in eftnode_cli_client.csr -CA eftnode_cli_ca.crt -CAkey eftnode_cli_ca.key -set_serial 01 -out eftnode_cli_client.crt

# Remove passphrase from Client Key
openssl rsa -passin pass:$password -in eftnode_cli_client.key -out eftnode_cli_client.key
