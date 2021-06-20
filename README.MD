English | [Русский](README.ru.MD)

[![Qt5 Utility Boilerplate by TheLongRunSmoke]()](#)

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

[![Style](https://github.com/TheLongRunSmoke/utility-boilerplate-qt/actions/workflows/style.yml/badge.svg)](https://github.com/TheLongRunSmoke/utility-boilerplate-qt/actions/workflows/style.yml)
[![Ubuntu build](https://github.com/TheLongRunSmoke/utility-boilerplate-qt/actions/workflows/ubuntu-build.yml/badge.svg)](https://github.com/TheLongRunSmoke/utility-boilerplate-qt/actions/workflows/ubuntu-build.yml)

# What is it?

Template for creating simple cross-platform application with GUI based on Qt.

You can go straight to developing widget contained target functionality.

**Features:**

* Ready-to-go template.
* Cross-platform. Can be build for Windows, Linux, any OS that Qt support.
* Minimal architecture and directory structure, to keep coupling low.
* Settings system, with OS independent storage and behavior.
* Test suites and code coverage already setup.
* Code style enforcing tooling.
* Internationalization support.
* No Boost.
* Cmake as build system.
* Basic CI, based on GitHub Actions.

# How to build?

## Requirements installation

You need Qt 5.12 at least.

### Windows

Install Qt from [official site](https://www.qt.io/download).

### Linux

Examples for Ubuntu 20.04, for another version or distributive refer to [Qt Wiki](https://wiki.qt.io/Main).

```shell
sudo apt install build-essential qt5-default qttools5-dev-tools
```

### Other systems

See [Qt Wiki](https://wiki.qt.io/Main).

## Build

In-source build restricted. From source folder do:

```shell
mkdir build
cd build/
cmake ../
cmake --build .
```

# Example

# Internationalization support

This boilerplate code include Qt internationalization support.

You need to create application translation files to make it work.

Take a note, for now module `utility_boilerplate_qt5` support only 2 languages:

1. English - in-built to sources
2. Russian

Pull requests with another language are welcome.

## How to assemble new translation?

ru_RU as example, use your language code.

1. Collect all strings inside `tr()` to TS file using `lupdate`.

   ```shell
   lupdate *.cpp -ts i18n/ru/app_ru.ts
   ```

2. Open it in translation tool and translate.

   ```shell
   linguist i18n/ru/app_ru.ts
   ```

3. Qt can load only one translation file at ones, so you need to collect a complete translation file with `lconvert`.
   Search for Qt `qtbase_<language code>.ts` in distribution package
   or [repository](https://github.com/qt/qttranslations/tree/dev/translations) and place it in to `i18n/<language code>`
   folder. Next merge TS files to one using `lconvert`.
   ```shell
   cd i18n/
   lconvert -i ru/*.ts ../../utility_boilerplate_qt5/i18n/ru/*.ts -o ru/appcomp_ru.ts
   ```

4. At last convert TS file to QM file using `lrelease`. Build system automatically copy all QM files to appropriate
   location, where binaries can find it.

   ```shell
   lrelease ru/appcomp_ru.ts ru/appcomp_ru.qm
   ```

5. To check that translation load correctly run application from command line and look
   for `Translation for "<language code>" load successfully` message. If translation can't be load you
   see `Can't load translation for "<language code>"` message. Qt do not offer more debug information for that.

# Code style enforcement

Project offer code style enforcement via clang-format and cmake-format. IDEA styles included.

Style workflow failed if any project file has bad formatting.

Format enforcing ignored if requirements not installed.

## Install requirements

### Windows

`clang-format` can be [downloaded](https://llvm.org/builds/) with LLVM package.

`cmake-format` installed using `pip`.

```shell
pip install cmakelang pyyaml
```

### Linux

Normally, linux systems has all requirements, except `cmake-format`.

```shell
pip install cmakelang
```

## Using

Fix all files in project.

```shell
cmake --build build --target fix-format
```
