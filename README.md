# greenServe-modules

GreenServe-Modules are published here.

This repository contains native Linux modules for the greenServe programming language.

Currently published modules:

* `libserver` — HTTP server, routing, cookies, sessions, HTTP requests and server functionality
* `gsnum` — numerical computing and scientific mathematics functionality

---

# Modules

## libserver

Current release:

```text
libserver-v1.0.1
```

Package:

```text
greenServe-server-module-linux-x86_64.zip
```

The package contains:

```text
libserver.so
```

## gsnum

Current release:

```text
gsnum-v1.0.0
```

Package:

```text
greenServe-gsnum-module-linux-x86_64.zip
```

The package contains:

```text
gsnum.so
```

Both modules are distributed as Linux x86_64 ZIP packages.

---

# Install libserver

The `libserver` module can be installed system-wide with the Makefile below.

The Makefile downloads the ZIP package, extracts `libserver.so`, and installs it into the first available greenServe module directory.

### Makefile

```makefile
LIBSERVER_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/libserver-v1.0.1/greenServe-server-module-linux-x86_64.zip

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

Save the Makefile as:

```text
Makefile
```

Then run:

```bash
sudo make install
```

The Makefile downloads:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/libserver-v1.0.1/greenServe-server-module-linux-x86_64.zip
```

It extracts:

```text
libserver.so
```

and installs it into the first available directory:

```text
/usr/local/lib/greenServe/modules
/usr/lib/greenServe/modules
/usr/lib64/greenServe/modules
```

The directory is selected automatically.

---

# Install gsnum

The `gsnum` module is distributed separately as version `1.0.0`.

Release:

```text
gsnum-v1.0.0
```

Package:

```text
greenServe-gsnum-module-linux-x86_64.zip
```

The package contains:

```text
gsnum.so
```

Use the following Makefile to install `gsnum.so` system-wide.

### Makefile

```makefile
GSNUM_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnum-v1.0.0/greenServe-gsnum-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-gsnum-install
ZIP_FILE := $(TMP_DIR)/greenServe-gsnum-module-linux-x86_64.zip

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
	echo "Downloading gsnum..."; \
	curl -fL "$(GSNUM_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting gsnum.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "gsnum.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: gsnum.so was not found in the package"; \
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
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsnum.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "gsnum.so installed to $$MODULE_DIR/gsnum.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/gsnum.so"; \
	rm -f "$(MODULE_DIR_2)/gsnum.so"; \
	rm -f "$(MODULE_DIR_3)/gsnum.so"; \
	echo "gsnum.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

Save the Makefile as:

```text
Makefile
```

Then run:

```bash
sudo make install
```

The Makefile downloads:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnum-v1.0.0/greenServe-gsnum-module-linux-x86_64.zip
```

It extracts:

```text
gsnum.so
```

and installs it into one of:

```text
/usr/local/lib/greenServe/modules
/usr/lib/greenServe/modules
/usr/lib64/greenServe/modules
```

The directory is selected automatically.

---

# Install both modules

If you want both modules installed, keep the two Makefiles as separate files:

```text
Makefile.libserver
Makefile.gsnum
```

Then run:

```bash
sudo make -f Makefile.libserver install
sudo make -f Makefile.gsnum install
```

After installation:

```text
/usr/local/lib/greenServe/modules/
├── libserver.so
└── gsnum.so
```

The actual directory may instead be:

```text
/usr/lib/greenServe/modules
```

or:

```text
/usr/lib64/greenServe/modules
```

depending on which directory can be created or used.

---

# Use libserver from greenServe

Once installed, `libserver.so` can be imported from a `.gsve` program.

```gsve
import server;

server.get("/hello", func(req) {
    return server.json({
        "message": "Hello from greenServe"
    });
});

server.serve(8080, "./public");
```

The module is loaded from the system greenServe module directories, so `libserver.so` does not need to be copied into the project directory.

---

# Use gsnum from greenServe

Import the numerical module with:

```gsve
import gsnum;
```

Example:

```gsve
import gsnum;

print(gsnum.sqrt(81));
print(gsnum.pow(2, 8));
print(gsnum.abs(-25));
print(gsnum.sin(0));
```

Output:

```text
9
256
25
0
```

---

# gsnum numerical operations

`gsnum` provides native numerical functionality for greenServe programs.

## Basic mathematics

```gsve
import gsnum;

print(gsnum.abs(-10));
print(gsnum.sqrt(64));
print(gsnum.cbrt(27));
print(gsnum.pow(2, 10));
print(gsnum.exp(1));
print(gsnum.log(10));
print(gsnum.log10(1000));
print(gsnum.log2(1024));
```

## Trigonometry

```gsve
import gsnum;

print(gsnum.sin(0));
print(gsnum.cos(0));
print(gsnum.tan(0));
print(gsnum.asin(0));
print(gsnum.acos(1));
print(gsnum.atan(1));
print(gsnum.atan2(10, 5));
```

## Arrays

```gsve
import gsnum;

define a = gsnum.zeros(5);
define b = gsnum.ones(5);
define c = gsnum.arange(0, 10, 2);

print(a);
print(b);
print(c);
```

## Statistics

```gsve
import gsnum;

define values = [10, 20, 30, 40, 50];

print(gsnum.sum(values));
print(gsnum.mean(values));
print(gsnum.median(values));
print(gsnum.var(values));
print(gsnum.std(values));
print(gsnum.min(values));
print(gsnum.max(values));
```

## Vector operations

```gsve
import gsnum;

define a = [1, 2, 3];
define b = [4, 5, 6];

print(gsnum.add(a, b));
print(gsnum.subtract(a, b));
print(gsnum.multiply(a, b));
print(gsnum.dot(a, b));
print(gsnum.norm(a));
print(gsnum.distance(a, b));
```

## Matrix operations

```gsve
import gsnum;

define a = [
    [1, 2],
    [3, 4]
];

define b = [
    [5, 6],
    [7, 8]
];

print(gsnum.matmul(a, b));
print(gsnum.transpose(a));
print(gsnum.det(a));
print(gsnum.trace(a));
print(gsnum.inverse(a));
```

## Matrix identity

```gsve
import gsnum;

define identity = gsnum.eye(3);

print(identity);
```

Result:

```text
[
    [1, 0, 0],
    [0, 1, 0],
    [0, 0, 1]
]
```

---

# Random numbers

`gsnum` also provides random numerical operations.

```gsve
import gsnum;

gsnum.seed(1234);

print(gsnum.random());
print(gsnum.randint(1, 100));

define values = gsnum.random_array(10);

print(values);
```

---

# Array transformations

```gsve
import gsnum;

define values = [1, 2, 3, 4, 5];

print(gsnum.cumsum(values));
print(gsnum.cumprod(values));
print(gsnum.diff(values));
print(gsnum.reverse(values));
print(gsnum.sort(values));
```

---

# Numerical module loading

greenServe automatically searches its system module directories for native modules.

The supported directories are:

```text
/usr/local/lib/greenServe/modules
/usr/lib/greenServe/modules
/usr/lib64/greenServe/modules
```

Therefore:

```gsve
import server;
```

loads:

```text
libserver.so
```

and:

```gsve
import gsnum;
```

loads:

```text
gsnum.so
```

The `.so` files do not need to be placed beside the `.gsve` source file.

---

# Remove libserver

Run:

```bash
sudo make uninstall
```

This removes:

```text
libserver.so
```

from all supported greenServe module directories.

---

# Remove gsnum

Run the `gsnum` Makefile's uninstall target:

```bash
sudo make uninstall
```

This removes:

```text
gsnum.so
```

from all supported greenServe module directories.

---

# Published Releases

## libserver

```text
Version: libserver-v1.0.1
Package: greenServe-server-module-linux-x86_64.zip
Library: libserver.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/libserver-v1.0.1/greenServe-server-module-linux-x86_64.zip
```

## gsnum

```text
Version: gsnum-v1.0.0
Package: greenServe-gsnum-module-linux-x86_64.zip
Library: gsnum.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnum-v1.0.0/greenServe-gsnum-module-linux-x86_64.zip
```

The published Linux packages contain the compiled native modules:

```text
greenServe-server-module-linux-x86_64.zip
└── libserver.so
```

and:

```text
greenServe-gsnum-module-linux-x86_64.zip
└── gsnum.so
```

---

# Summary

greenServe-Modules provides native shared libraries that extend the greenServe language.

Current modules:

| Module    | Version | Shared Library | Purpose                              |
| --------- | ------- | -------------- | ------------------------------------ |
| libserver | 1.0.1   | `libserver.so` | HTTP/server functionality            |
| gsnum     | 1.0.0   | `gsnum.so`     | Numerical and mathematical computing |

Both modules are installed system-wide and can be imported directly from `.gsve` programs without copying the `.so` files into the application directory.
