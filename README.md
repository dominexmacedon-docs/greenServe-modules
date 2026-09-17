# greenServe-modules

GreenServe-Modules are published here.

This repository contains native Linux modules for the greenServe programming language.

Currently published modules:

* `libserver` - HTTP server, routing, cookies, sessions, HTTP requests and server functionality
* `gsnum` - numerical computing and scientific mathematics functionality
* `gsvocab` - vocabulary and word-processing functionality
* `gsvector` - vector mathematics and vector operations
* `gstoken` - text tokenization and token-processing functionality
* `gssample` - sampling, choice and shuffling functionality
* `gsrandom` - random-number generation functionality
* `gsnn` - neural-network and machine-learning numerical functionality
* `gsmatrix` - matrix mathematics and matrix operations
* `gsembed` - text embedding and vector-similarity functionality

---

# Modules

## libserver

Current release:

```text
libserver-v1.0.2
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

## gsvocab

Current release:

```text
gsvocab-v1.0.0
```

Package:

```text
greenServe-gsvocab-module-linux-x86_64.zip
```

The package contains:

```text
gsvocab.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsvocab-v1.0.0/greenServe-gsvocab-module-linux-x86_64.zip
```

## gsvector

Current release:

```text
gsvector-v1.0.0
```

Package:

```text
greenServe-gsvector-module-linux-x86_64.zip
```

The package contains:

```text
gsvector.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsvector-v1.0.0/greenServe-gsvector-module-linux-x86_64.zip
```

## gstoken

Current release:

```text
gstoken-v1.0.0
```

Package:

```text
greenServe-gstoken-module-linux-x86_64.zip
```

The package contains:

```text
gstoken.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gstoken-v1.0.0/greenServe-gstoken-module-linux-x86_64.zip
```

## gssample

Current release:

```text
gssample-v1.0.0
```

Package:

```text
greenServe-gssample-module-linux-x86_64.zip
```

The package contains:

```text
gssample.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gssample-v1.0.0/greenServe-gssample-module-linux-x86_64.zip
```

## gsrandom

Current release:

```text
gsrandom-v1.0.0
```

Package:

```text
greenServe-gsrandom-module-linux-x86_64.zip
```

The package contains:

```text
gsrandom.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsrandom-v1.0.0/greenServe-gsrandom-module-linux-x86_64.zip
```

## gsnn

Current release:

```text
gsnn-v1.0.0
```

Package:

```text
greenServe-gsnn-module-linux-x86_64.zip
```

The package contains:

```text
gsnn.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnn-v1.0.0/greenServe-gsnn-module-linux-x86_64.zip
```

## gsmatrix

Current release:

```text
gsmatrix-v1.0.0
```

Package:

```text
greenServe-gsmatrix-module-linux-x86_64.zip
```

The package contains:

```text
gsmatrix.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsmatrix-v1.0.0/greenServe-gsmatrix-module-linux-x86_64.zip
```

## gsembed

Current release:

```text
gsembed-v1.0.0
```

Package:

```text
greenServe-gsembed-module-linux-x86_64.zip
```

The package contains:

```text
gsembed.so
```

Release package:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsembed-v1.0.0/greenServe-gsembed-module-linux-x86_64.zip
```

All modules are distributed as Linux x86_64 ZIP packages.

---

# Install libserver

The `libserver` module can be installed system-wide with the Makefile below.

The Makefile downloads the ZIP package, extracts `libserver.so`, and installs it into the first available greenServe module directory.

### Makefile

```makefile
LIBSERVER_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/libserver-v1.0.2/greenServe-server-module-linux-x86_64.zip

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
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/libserver-v1.0.2/greenServe-server-module-linux-x86_64.zip
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

```bash
sudo make install
```

The package is:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnum-v1.0.0/greenServe-gsnum-module-linux-x86_64.zip
```

---

# Install gsvocab

`gsvocab` provides vocabulary and word-processing functionality.

Release:

```text
gsvocab-v1.0.0
```

Package:

```text
greenServe-gsvocab-module-linux-x86_64.zip
```

### Makefile

```makefile
GSVOCAB_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsvocab-v1.0.0/greenServe-gsvocab-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-gsvocab-install
ZIP_FILE := $(TMP_DIR)/greenServe-gsvocab-module-linux-x86_64.zip

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
	echo "Downloading gsvocab..."; \
	curl -fL "$(GSVOCAB_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting gsvocab.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "gsvocab.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: gsvocab.so was not found in the package"; \
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
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsvocab.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "gsvocab.so installed to $$MODULE_DIR/gsvocab.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/gsvocab.so"; \
	rm -f "$(MODULE_DIR_2)/gsvocab.so"; \
	rm -f "$(MODULE_DIR_3)/gsvocab.so"; \
	echo "gsvocab.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

```bash
sudo make install
```

---

# Install gsvector

`gsvector` provides vector mathematics and vector operations.

Release:

```text
gsvector-v1.0.0
```

Package:

```text
greenServe-gsvector-module-linux-x86_64.zip
```

### Makefile

```makefile
GSVECTOR_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsvector-v1.0.0/greenServe-gsvector-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-gsvector-install
ZIP_FILE := $(TMP_DIR)/greenServe-gsvector-module-linux-x86_64.zip

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
	echo "Downloading gsvector..."; \
	curl -fL "$(GSVECTOR_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting gsvector.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "gsvector.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: gsvector.so was not found in the package"; \
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
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsvector.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "gsvector.so installed to $$MODULE_DIR/gsvector.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/gsvector.so"; \
	rm -f "$(MODULE_DIR_2)/gsvector.so"; \
	rm -f "$(MODULE_DIR_3)/gsvector.so"; \
	echo "gsvector.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

```bash
sudo make install
```

---

# Install gstoken

`gstoken` provides text tokenization and token-processing functionality.

Release:

```text
gstoken-v1.0.0
```

Package:

```text
greenServe-gstoken-module-linux-x86_64.zip
```

### Makefile

```makefile
GSTOKEN_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gstoken-v1.0.0/greenServe-gstoken-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-gstoken-install
ZIP_FILE := $(TMP_DIR)/greenServe-gstoken-module-linux-x86_64.zip

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
	echo "Downloading gstoken..."; \
	curl -fL "$(GSTOKEN_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting gstoken.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "gstoken.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: gstoken.so was not found in the package"; \
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
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gstoken.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "gstoken.so installed to $$MODULE_DIR/gstoken.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/gstoken.so"; \
	rm -f "$(MODULE_DIR_2)/gstoken.so"; \
	rm -f "$(MODULE_DIR_3)/gstoken.so"; \
	echo "gstoken.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

```bash
sudo make install
```

---

# Install gssample

`gssample` provides sampling, choice and shuffling functionality.

Release:

```text
gssample-v1.0.0
```

Package:

```text
greenServe-gssample-module-linux-x86_64.zip
```

### Makefile

```makefile
GSSAMPLE_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gssample-v1.0.0/greenServe-gssample-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-gssample-install
ZIP_FILE := $(TMP_DIR)/greenServe-gssample-module-linux-x86_64.zip

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
	echo "Downloading gssample..."; \
	curl -fL "$(GSSAMPLE_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting gssample.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "gssample.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: gssample.so was not found in the package"; \
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
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gssample.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "gssample.so installed to $$MODULE_DIR/gssample.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/gssample.so"; \
	rm -f "$(MODULE_DIR_2)/gssample.so"; \
	rm -f "$(MODULE_DIR_3)/gssample.so"; \
	echo "gssample.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

```bash
sudo make install
```

---

# Install gsrandom

`gsrandom` provides random-number generation functionality.

Release:

```text
gsrandom-v1.0.0
```

Package:

```text
greenServe-gsrandom-module-linux-x86_64.zip
```

### Makefile

```makefile
GSRANDOM_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsrandom-v1.0.0/greenServe-gsrandom-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-gsrandom-install
ZIP_FILE := $(TMP_DIR)/greenServe-gsrandom-module-linux-x86_64.zip

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
	echo "Downloading gsrandom..."; \
	curl -fL "$(GSRANDOM_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting gsrandom.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "gsrandom.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: gsrandom.so was not found in the package"; \
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
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsrandom.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "gsrandom.so installed to $$MODULE_DIR/gsrandom.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/gsrandom.so"; \
	rm -f "$(MODULE_DIR_2)/gsrandom.so"; \
	rm -f "$(MODULE_DIR_3)/gsrandom.so"; \
	echo "gsrandom.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

```bash
sudo make install
```

---

# Install gsnn

`gsnn` provides neural-network and machine-learning numerical functionality.

Release:

```text
gsnn-v1.0.0
```

Package:

```text
greenServe-gsnn-module-linux-x86_64.zip
```

### Makefile

```makefile
GSNN_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnn-v1.0.0/greenServe-gsnn-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-gsnn-install
ZIP_FILE := $(TMP_DIR)/greenServe-gsnn-module-linux-x86_64.zip

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
	echo "Downloading gsnn..."; \
	curl -fL "$(GSNN_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting gsnn.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "gsnn.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: gsnn.so was not found in the package"; \
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
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsnn.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "gsnn.so installed to $$MODULE_DIR/gsnn.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/gsnn.so"; \
	rm -f "$(MODULE_DIR_2)/gsnn.so"; \
	rm -f "$(MODULE_DIR_3)/gsnn.so"; \
	echo "gsnn.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

```bash
sudo make install
```

---

# Install gsmatrix

`gsmatrix` provides matrix mathematics and matrix operations.

Release:

```text
gsmatrix-v1.0.0
```

Package:

```text
greenServe-gsmatrix-module-linux-x86_64.zip
```

### Makefile

```makefile
GSMATRIX_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsmatrix-v1.0.0/greenServe-gsmatrix-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-gsmatrix-install
ZIP_FILE := $(TMP_DIR)/greenServe-gsmatrix-module-linux-x86_64.zip

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
	echo "Downloading gsmatrix..."; \
	curl -fL "$(GSMATRIX_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting gsmatrix.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "gsmatrix.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: gsmatrix.so was not found in the package"; \
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
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsmatrix.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "gsmatrix.so installed to $$MODULE_DIR/gsmatrix.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/gsmatrix.so"; \
	rm -f "$(MODULE_DIR_2)/gsmatrix.so"; \
	rm -f "$(MODULE_DIR_3)/gsmatrix.so"; \
	echo "gsmatrix.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

```bash
sudo make install
```

---

# Install gsembed

`gsembed` provides text embedding and vector-similarity functionality.

Release:

```text
gsembed-v1.0.0
```

Package:

```text
greenServe-gsembed-module-linux-x86_64.zip
```

### Makefile

```makefile
GSEMBED_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsembed-v1.0.0/greenServe-gsembed-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-gsembed-install
ZIP_FILE := $(TMP_DIR)/greenServe-gsembed-module-linux-x86_64.zip

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
	echo "Downloading gsembed..."; \
	curl -fL "$(GSEMBED_URL)" -o "$(ZIP_FILE)"; \
	echo "Extracting gsembed.so..."; \
	unzip -o "$(ZIP_FILE)" -d "$(TMP_DIR)/extracted"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted" -type f -name "gsembed.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then \
		echo "Error: gsembed.so was not found in the package"; \
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
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsembed.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo "gsembed.so installed to $$MODULE_DIR/gsembed.so"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/gsembed.so"; \
	rm -f "$(MODULE_DIR_2)/gsembed.so"; \
	rm -f "$(MODULE_DIR_3)/gsembed.so"; \
	echo "gsembed.so removed"

clean:
	rm -rf "$(TMP_DIR)"
```

## Install

```bash
sudo make install
```

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

# Use gsvocab from greenServe

```gsve
import gsvocab;

define words = gsvocab.words("greenServe is a programming language");

print(words);
print(gsvocab.size(words));
```

---

# Use gstoken from greenServe

```gsve
import gstoken;

define tokens = gstoken.tokenize("greenServe programming language");

print(tokens);
print(gstoken.count("greenServe programming language"));
```

---

# Use gsvector from greenServe

```gsve
import gsvector;

define a = [1, 2, 3];
define b = [4, 5, 6];

print(gsvector.add(a, b));
print(gsvector.subtract(a, b));
print(gsvector.dot(a, b));
print(gsvector.norm(a));
print(gsvector.distance(a, b));
```

---

# Use gsmatrix from greenServe

```gsve
import gsmatrix;

define a = [
    [1, 2],
    [3, 4]
];

define b = [
    [5, 6],
    [7, 8]
];

print(gsmatrix.matmul(a, b));
print(gsmatrix.transpose(a));
print(gsmatrix.det(a));
print(gsmatrix.trace(a));
print(gsmatrix.inverse(a));
```

---

# Use gsembed from greenServe

```gsve
import gsembed;

define a = gsembed.embed("greenServe programming language");
define b = gsembed.embed("server programming");

print(a);
print(b);
print(gsembed.cosine(a, b));
```

---

# Use gsrandom from greenServe

```gsve
import gsrandom;

gsrandom.seed(1234);

print(gsrandom.random());
print(gsrandom.randint(1, 100));

define values = gsrandom.random_array(10);

print(values);
```

---

# Use gssample from greenServe

```gsve
import gssample;

define values = [1, 2, 3, 4, 5];

print(gssample.choice(values));
print(gssample.sample(values, 3));
print(gssample.shuffle(values));
```

---

# Use gsnn from greenServe

```gsve
import gsnn;

print(gsnn.sigmoid(0));
print(gsnn.relu(-5));
print(gsnn.relu(5));

define values = [1, 2, 3];

print(gsnn.softmax(values));
print(gsnn.argmax(values));
```

---

# Numerical computing with gsnum

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

---

# Random numbers with gsrandom

```gsve
import gsrandom;

gsrandom.seed(1234);

define value = gsrandom.random();
define number = gsrandom.randint(1, 100);

print(value);
print(number);
```

---

# Sampling with gssample

```gsve
import gssample;

define values = [10, 20, 30, 40, 50];

define selected = gssample.sample(values, 3);

print(selected);
```

---

# Tokenization with gstoken

```gsve
import gstoken;

define text = "greenServe is a programming language";

define tokens = gstoken.tokenize(text);

print(tokens);
print(gstoken.count(text));
```

---

# Vocabulary with gsvocab

```gsve
import gsvocab;

define text = "greenServe is a programming language";

define vocabulary = gsvocab.build(text);

print(vocabulary);
```

---

# Vector operations with gsvector

```gsve
import gsvector;

define a = [1, 2, 3];
define b = [4, 5, 6];

define sum = gsvector.add(a, b);
define difference = gsvector.subtract(a, b);
define product = gsvector.multiply(a, b);

print(sum);
print(difference);
print(product);
print(gsvector.dot(a, b));
print(gsvector.norm(a));
```

---

# Matrix operations with gsmatrix

```gsve
import gsmatrix;

define matrix = [
    [1, 2],
    [3, 4]
];

print(gsmatrix.transpose(matrix));
print(gsmatrix.trace(matrix));
print(gsmatrix.det(matrix));
```

---

# Embeddings with gsembed

```gsve
import gsembed;

define first = gsembed.embed("greenServe");
define second = gsembed.embed("programming language");

print(first);
print(second);
print(gsembed.cosine(first, second));
```

---

# Neural-network operations with gsnn

```gsve
import gsnn;

define values = [1, 2, 3];

define probabilities = gsnn.softmax(values);

print(probabilities);
print(gsnn.argmax(probabilities));
```

---

# Module loading

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

Likewise:

```gsve
import gsvocab;
import gsvector;
import gstoken;
import gssample;
import gsrandom;
import gsnn;
import gsmatrix;
import gsembed;
```

load:

```text
gsvocab.so
gsvector.so
gstoken.so
gssample.so
gsrandom.so
gsnn.so
gsmatrix.so
gsembed.so
```

The `.so` files do not need to be placed beside the `.gsve` source file.

---

# Install all modules

The following single Makefile installs all currently published greenServe modules.

Save it as:

```text
Makefile
```

Then run:

```bash
sudo make install
```

### Combined Makefile

```makefile
LIBSERVER_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/libserver-v1.0.2/greenServe-server-module-linux-x86_64.zip
GSNUM_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnum-v1.0.0/greenServe-gsnum-module-linux-x86_64.zip
GSVOCAB_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsvocab-v1.0.0/greenServe-gsvocab-module-linux-x86_64.zip
GSVECTOR_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsvector-v1.0.0/greenServe-gsvector-module-linux-x86_64.zip
GSTOKEN_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gstoken-v1.0.0/greenServe-gstoken-module-linux-x86_64.zip
GSSAMPLE_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gssample-v1.0.0/greenServe-gssample-module-linux-x86_64.zip
GSRANDOM_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsrandom-v1.0.0/greenServe-gsrandom-module-linux-x86_64.zip
GSNN_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnn-v1.0.0/greenServe-gsnn-module-linux-x86_64.zip
GSMATRIX_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsmatrix-v1.0.0/greenServe-gsmatrix-module-linux-x86_64.zip
GSEMBED_URL := https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsembed-v1.0.0/greenServe-gsembed-module-linux-x86_64.zip

TMP_DIR := /tmp/greenServe-modules-install

MODULE_DIR_1 := /usr/local/lib/greenServe/modules
MODULE_DIR_2 := /usr/lib/greenServe/modules
MODULE_DIR_3 := /usr/lib64/greenServe/modules

MODULES := \
	libserver.so \
	gsnum.so \
	gsvocab.so \
	gsvector.so \
	gstoken.so \
	gssample.so \
	gsrandom.so \
	gsnn.so \
	gsmatrix.so \
	gsembed.so

.PHONY: install uninstall clean

install:
	@set -e; \
	command -v curl >/dev/null 2>&1 || { echo "curl is required"; exit 1; }; \
	command -v unzip >/dev/null 2>&1 || { echo "unzip is required"; exit 1; }; \
	rm -rf "$(TMP_DIR)"; \
	mkdir -p "$(TMP_DIR)/extracted"; \
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
	echo "Installing greenServe native modules to $$MODULE_DIR"; \
	echo "Downloading libserver..."; \
	curl -fL "$(LIBSERVER_URL)" -o "$(TMP_DIR)/libserver.zip"; \
	unzip -o "$(TMP_DIR)/libserver.zip" -d "$(TMP_DIR)/extracted/libserver"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/libserver" -type f -name "libserver.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: libserver.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/libserver.so"; \
	echo "Downloading gsnum..."; \
	curl -fL "$(GSNUM_URL)" -o "$(TMP_DIR)/gsnum.zip"; \
	unzip -o "$(TMP_DIR)/gsnum.zip" -d "$(TMP_DIR)/extracted/gsnum"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/gsnum" -type f -name "gsnum.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: gsnum.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsnum.so"; \
	echo "Downloading gsvocab..."; \
	curl -fL "$(GSVOCAB_URL)" -o "$(TMP_DIR)/gsvocab.zip"; \
	unzip -o "$(TMP_DIR)/gsvocab.zip" -d "$(TMP_DIR)/extracted/gsvocab"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/gsvocab" -type f -name "gsvocab.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: gsvocab.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsvocab.so"; \
	echo "Downloading gsvector..."; \
	curl -fL "$(GSVECTOR_URL)" -o "$(TMP_DIR)/gsvector.zip"; \
	unzip -o "$(TMP_DIR)/gsvector.zip" -d "$(TMP_DIR)/extracted/gsvector"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/gsvector" -type f -name "gsvector.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: gsvector.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsvector.so"; \
	echo "Downloading gstoken..."; \
	curl -fL "$(GSTOKEN_URL)" -o "$(TMP_DIR)/gstoken.zip"; \
	unzip -o "$(TMP_DIR)/gstoken.zip" -d "$(TMP_DIR)/extracted/gstoken"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/gstoken" -type f -name "gstoken.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: gstoken.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gstoken.so"; \
	echo "Downloading gssample..."; \
	curl -fL "$(GSSAMPLE_URL)" -o "$(TMP_DIR)/gssample.zip"; \
	unzip -o "$(TMP_DIR)/gssample.zip" -d "$(TMP_DIR)/extracted/gssample"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/gssample" -type f -name "gssample.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: gssample.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gssample.so"; \
	echo "Downloading gsrandom..."; \
	curl -fL "$(GSRANDOM_URL)" -o "$(TMP_DIR)/gsrandom.zip"; \
	unzip -o "$(TMP_DIR)/gsrandom.zip" -d "$(TMP_DIR)/extracted/gsrandom"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/gsrandom" -type f -name "gsrandom.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: gsrandom.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsrandom.so"; \
	echo "Downloading gsnn..."; \
	curl -fL "$(GSNN_URL)" -o "$(TMP_DIR)/gsnn.zip"; \
	unzip -o "$(TMP_DIR)/gsnn.zip" -d "$(TMP_DIR)/extracted/gsnn"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/gsnn" -type f -name "gsnn.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: gsnn.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsnn.so"; \
	echo "Downloading gsmatrix..."; \
	curl -fL "$(GSMATRIX_URL)" -o "$(TMP_DIR)/gsmatrix.zip"; \
	unzip -o "$(TMP_DIR)/gsmatrix.zip" -d "$(TMP_DIR)/extracted/gsmatrix"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/gsmatrix" -type f -name "gsmatrix.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: gsmatrix.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsmatrix.so"; \
	echo "Downloading gsembed..."; \
	curl -fL "$(GSEMBED_URL)" -o "$(TMP_DIR)/gsembed.zip"; \
	unzip -o "$(TMP_DIR)/gsembed.zip" -d "$(TMP_DIR)/extracted/gsembed"; \
	SO_FILE=$$(find "$(TMP_DIR)/extracted/gsembed" -type f -name "gsembed.so" -print -quit); \
	if [ -z "$$SO_FILE" ]; then echo "Error: gsembed.so not found"; exit 1; fi; \
	install -m 755 "$$SO_FILE" "$$MODULE_DIR/gsembed.so"; \
	rm -rf "$(TMP_DIR)"; \
	echo ""; \
	echo "All greenServe modules installed successfully."; \
	echo "Module directory: $$MODULE_DIR"; \
	ls -lh "$$MODULE_DIR"

uninstall:
	@set -e; \
	rm -f "$(MODULE_DIR_1)/libserver.so"; \
	rm -f "$(MODULE_DIR_1)/gsnum.so"; \
	rm -f "$(MODULE_DIR_1)/gsvocab.so"; \
	rm -f "$(MODULE_DIR_1)/gsvector.so"; \
	rm -f "$(MODULE_DIR_1)/gstoken.so"; \
	rm -f "$(MODULE_DIR_1)/gssample.so"; \
	rm -f "$(MODULE_DIR_1)/gsrandom.so"; \
	rm -f "$(MODULE_DIR_1)/gsnn.so"; \
	rm -f "$(MODULE_DIR_1)/gsmatrix.so"; \
	rm -f "$(MODULE_DIR_1)/gsembed.so"; \
	rm -f "$(MODULE_DIR_2)/libserver.so"; \
	rm -f "$(MODULE_DIR_2)/gsnum.so"; \
	rm -f "$(MODULE_DIR_2)/gsvocab.so"; \
	rm -f "$(MODULE_DIR_2)/gsvector.so"; \
	rm -f "$(MODULE_DIR_2)/gstoken.so"; \
	rm -f "$(MODULE_DIR_2)/gssample.so"; \
	rm -f "$(MODULE_DIR_2)/gsrandom.so"; \
	rm -f "$(MODULE_DIR_2)/gsnn.so"; \
	rm -f "$(MODULE_DIR_2)/gsmatrix.so"; \
	rm -f "$(MODULE_DIR_2)/gsembed.so"; \
	rm -f "$(MODULE_DIR_3)/libserver.so"; \
	rm -f "$(MODULE_DIR_3)/gsnum.so"; \
	rm -f "$(MODULE_DIR_3)/gsvocab.so"; \
	rm -f "$(MODULE_DIR_3)/gsvector.so"; \
	rm -f "$(MODULE_DIR_3)/gstoken.so"; \
	rm -f "$(MODULE_DIR_3)/gssample.so"; \
	rm -f "$(MODULE_DIR_3)/gsrandom.so"; \
	rm -f "$(MODULE_DIR_3)/gsnn.so"; \
	rm -f "$(MODULE_DIR_3)/gsmatrix.so"; \
	rm -f "$(MODULE_DIR_3)/gsembed.so"; \
	echo "All greenServe modules removed"

clean:
	rm -rf "$(TMP_DIR)"
```

After installation, the module directory contains:

```text
/usr/local/lib/greenServe/modules/
├── libserver.so
├── gsnum.so
├── gsvocab.so
├── gsvector.so
├── gstoken.so
├── gssample.so
├── gsrandom.so
├── gsnn.so
├── gsmatrix.so
└── gsembed.so
```

The actual directory may instead be:

```text
/usr/lib/greenServe/modules
```

or:

```text
/usr/lib64/greenServe/modules
```

depending on which directory is available.

---

# Remove all modules

If the combined Makefile is being used:

```bash
sudo make uninstall
```

This removes all published greenServe native modules from the supported system module directories.

---

# Published Releases

## libserver

```text
Version: libserver-v1.0.2
Package: greenServe-server-module-linux-x86_64.zip
Library: libserver.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/libserver-v1.0.1/greenServe-server-module-linux-x86_64.zip
```

## gsnum

```text
Version: gsnum-v1.0.0
Package: greenServe-gsnum-module-linux-x86_64.zip
Library: gsnum.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnum-v1.0.0/greenServe-gsnum-module-linux-x86_64.zip
```

## gsvocab

```text
Version: gsvocab-v1.0.0
Package: greenServe-gsvocab-module-linux-x86_64.zip
Library: gsvocab.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsvocab-v1.0.0/greenServe-gsvocab-module-linux-x86_64.zip
```

## gsvector

```text
Version: gsvector-v1.0.0
Package: greenServe-gsvector-module-linux-x86_64.zip
Library: gsvector.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsvector-v1.0.0/greenServe-gsvector-module-linux-x86_64.zip
```

## gstoken

```text
Version: gstoken-v1.0.0
Package: greenServe-gstoken-module-linux-x86_64.zip
Library: gstoken.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gstoken-v1.0.0/greenServe-gstoken-module-linux-x86_64.zip
```

## gssample

```text
Version: gssample-v1.0.0
Package: greenServe-gssample-module-linux-x86_64.zip
Library: gssample.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gssample-v1.0.0/greenServe-gssample-module-linux-x86_64.zip
```

## gsrandom

```text
Version: gsrandom-v1.0.0
Package: greenServe-gsrandom-module-linux-x86_64.zip
Library: gsrandom.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsrandom-v1.0.0/greenServe-gsrandom-module-linux-x86_64.zip
```

## gsnn

```text
Version: gsnn-v1.0.0
Package: greenServe-gsnn-module-linux-x86_64.zip
Library: gsnn.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsnn-v1.0.0/greenServe-gsnn-module-linux-x86_64.zip
```

## gsmatrix

```text
Version: gsmatrix-v1.0.0
Package: greenServe-gsmatrix-module-linux-x86_64.zip
Library: gsmatrix.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsmatrix-v1.0.0/greenServe-gsmatrix-module-linux-x86_64.zip
```

## gsembed

```text
Version: gsembed-v1.0.0
Package: greenServe-gsembed-module-linux-x86_64.zip
Library: gsembed.so
```

Release:

```text
https://github.com/dominexmacedon-docs/greenServe-modules/releases/download/gsembed-v1.0.0/greenServe-gsembed-module-linux-x86_64.zip
```

---

# Summary

greenServe-Modules provides native shared libraries that extend the greenServe language.

Current modules:

| Module    | Version | Shared Library | Purpose                               |
| --------- | ------- | -------------- | ------------------------------------- |
| libserver | 1.0.1   | `libserver.so` | HTTP/server functionality             |
| gsnum     | 1.0.0   | `gsnum.so`     | Numerical and mathematical computing  |
| gsvocab   | 1.0.0   | `gsvocab.so`   | Vocabulary and word processing        |
| gsvector  | 1.0.0   | `gsvector.so`  | Vector mathematics                    |
| gstoken   | 1.0.0   | `gstoken.so`   | Text tokenization                     |
| gssample  | 1.0.0   | `gssample.so`  | Sampling and shuffling                |
| gsrandom  | 1.0.0   | `gsrandom.so`  | Random-number generation              |
| gsnn      | 1.0.0   | `gsnn.so`      | Neural-network numerical operations   |
| gsmatrix  | 1.0.0   | `gsmatrix.so`  | Matrix mathematics                    |
| gsembed   | 1.0.0   | `gsembed.so`   | Text embeddings and vector similarity |

All modules are Linux x86_64 native shared libraries and are loaded by greenServe from its system module directories.

The `.so` files do not need to be copied into individual greenServe projects. Once installed system-wide, they can be imported directly from `.gsve` programs.
