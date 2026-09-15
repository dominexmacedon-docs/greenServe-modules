# greenServe-modules

GreenServe-Modules are published here.

## Install libserver

The `libserver` module is distributed as a Linux x86_64 ZIP package.

The Makefile below downloads the package, extracts `libserver.so`, and installs it into a system-wide greenServe module directory.
The first directory that can be created or used is selected automatically.

### Makefile

```makefile
LIBSERVER_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/libserver-v1.0.0/greenServe-server-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-libserver-install
ZIP_FILE := $(TMP_DIR)/greenServe-server-module-linux-x86_64.zip

MODULE_DIR_1 := /usr/local/lib/greenServe/modules
MODULE_DIR_2 := /usr/lib/greenServe/modules
MODULE_DIR_3 := /usr/lib64/greenServe/modules

.PHONY: install uninstall clean

install:
	@set -e; \
	command -v curl >/dev/null 2>&1 || { echo "curl is required"; exit 1; }; \
	command -v unzip >/dev/null 2>&1 || { echo "unzip is required"; exit 1; }; \
	rm -rf "$(TMP_DIR)"; \
	mkdir -p "$(TMP_DIR)/extracted"; \
	echo "Downloading libserver..."; \
	curl -fL "$(LIBSERVER_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting libserver.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "libserver.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: libserver.so was not found in the package"; \
		rm -rf "$(TMP_DIR)"; \
		exit 1; \
	fi; \
	if mkdir -p "$(MODULE_DIR_1)" 2>/dev/null; then \
		MODULE_DIR="$(MODULE_DIR_1)"; \
	elif mkdir -p "$(MODULE_DIR_2)" 2>/dev/null; then \
		MODULE_DIR="$(MODULE_DIR_2)"; \
	elif mkdir -p "$(MODULE_DIR_3)" 2>/dev/null; then \
		MODULE_DIR="$(MODULE_DIR_3)"; \
	else \
		echo "Error: could not create a greenServe module directory"; \
		rm -rf "$(TMP_DIR)"; \
		exit 1; \
	fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/libserver.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "libserver.so installed to $$MODULE_DIR/libserver.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/libserver.so"; \
	rm -f "$(MODULE_DIR_2)/libserver.so"; \
	rm -f "$(MODULE_DIR_3)/libserver.so"; \
	echo "libserver.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

Save the Makefile above as `Makefile`, then run:

```bash
sudo make install
```

The Makefile downloads:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/libserver-v1.0.0/greenServe-server-module-linux-x86_64.zip
```

It extracts:

```text
libserver.so
```

and installs it into one of:

```text
/usr/local/lib/greenServe/modules
/usr/lib/greenServe/modules
/usr/lib64/greenServe/modules
```

The directory is selected automatically.

## Use from greenServe

After installation, the module can be imported from a `.gsve` program:

```gsve
import server;

define response = http_get("http://example.com");

print(response.status);
print(response.body);
```

Or:

```gsve
import server;

serve(8080, "./public");
```

greenServe searches its system module directories automatically, so `libserver.so` does not need to be copied into the project directory.

## Remove the module

```bash
sudo make uninstall
```

This removes `libserver.so` from all three supported greenServe module directories.

```

This keeps the **ZIP as the published package** and `libserver.so` as the actual greenServe module that gets installed.
```
