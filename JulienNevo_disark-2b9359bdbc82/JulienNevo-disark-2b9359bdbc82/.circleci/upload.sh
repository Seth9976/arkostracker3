#!/bin/bash

# Parameter 1: Input file ("Disark.zip").
# Parameter 2: File to rename the input file into ("Disark-windows-1.0.0.zip").
# Parameter 3: Version for the target folder ("1.0.0").
# Parameter 4: Target name for the target folder ("linux64").

echo "Uploading..."

# Rename a simple generated file ("Disark.zip") into a more complex filename ("Disark-windows-1.0.0.zip").
mv "$1" "$2"

echo "Moving $1 to $2"

# Upload via FTP.
# Error handling: https://stackoverflow.com/questions/57120898/capturing-error-message-of-curl-in-bash-script-andchecking-status
m=$(curl -v -T "$2" "ftp://${FTP_USERNAME}:${FTP_PASSWORD}@${FTP_RELEASE_BASE_URL}/$3/$4/" --ftp-create-dirs 2>&1)
if [ $? -ne 0 ] ; then
   echo "Error: ""$m"
   exit 1
else
  echo "Uploaded."
fi