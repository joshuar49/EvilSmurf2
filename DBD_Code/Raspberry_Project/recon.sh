#!/bin/bash

bt_commands="
agent on
pairable on
discoverable on
scan on
"

sleep_sec="$1"
file_name="$2"
{ echo -e "$bt_commands"; sleep "$sleep_sec"; } | sudo bluetoothctl > "$file_name"

echo -e "scan off" | sudo bluetoothctl >> "$file_name"
