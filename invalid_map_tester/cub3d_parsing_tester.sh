#!/bin/bash

CUB3D_PATH="${1:-.}"
CUB3D_EXEC="$CUB3D_PATH/cub3D"
MAPS_DIR="invalid_maps"

echo "Testing $CUB3D_EXEC."

if [ ! -x "$CUB3D_EXEC" ]; then
    echo "Error: $CUB3D_EXEC not found or not executable."
    exit 2
fi

total=0
passed=0
failed=0
failed_files=()

while IFS= read -r -d '' mapfile; do
    ((total++))
    timeout 2 "$CUB3D_EXEC" "$mapfile" > /dev/null 2>&1
    exit_code=$?
    if [ $exit_code -ne 0 ] && [ $exit_code -ne 124 ]; then
        echo "[OK]   $mapfile"
        ((passed++))
    else
        echo "[FAIL] $mapfile (exit code $exit_code)"
        ((failed++))
        failed_files+=("$mapfile")
    fi
done < <(find "$MAPS_DIR" -type f -print0)

echo
echo "Tested $total files: $passed passed, $failed failed."
if [ $failed -ne 0 ]; then
    echo
    echo "Failed files:"
    for f in "${failed_files[@]}"; do
        echo "  $f"
    done
    exit 1
else
    exit
fi
