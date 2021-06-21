[English](README.MD) | Русский

[![Qt5 Utility Boilerplate by TheLongRunSmoke]()](#)

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
[![Style](https://github.com/TheLongRunSmoke/utility-boilerplate-qt/actions/workflows/style.yml/badge.svg)](https://github.com/TheLongRunSmoke/utility-boilerplate-qt/actions/workflows/style.yml)
[![Ubuntu build](https://github.com/TheLongRunSmoke/utility-boilerplate-qt/actions/workflows/ubuntu-build.yml/badge.svg)](https://github.com/TheLongRunSmoke/utility-boilerplate-qt/actions/workflows/ubuntu-build.yml)

# Что это?

Шаблон для создания простого кроссплатформенного приложения с графическим интерфейсом на базе Qt.

Можно начинать прямо с разработки виджета содержащего целевой функционал.

**Особенности:**

* Готовый шаблон. Не требует дополнительной подготовки к работе.
* Кроссплатформенный. Может быть собран для Windows, Linux, любой ОС поддерживаемой Qt.
* Минимальная архитектура и структура директорий, обеспечивающие пониженное зацепление.
* Система настроек, независимая от ОС.
* Наборы тестов и покрытие уже настроены.
* Инструменты контроля стиля кода.
* Поддержка интернационализации.
* Нет Boost.
* Cmake как система сборки.
* Базовый CI на основе GitHub Actions.

# Как собрать?

## Установка зависимостей

Нужен Qt 5.12 или выше.

### Windows

Установите Qt c [официального сайта](https://www.qt.io/download).

### Linux

Пример для Ubuntu 20.04, для других версий или дистрибутивов смотрите [Qt Wiki](https://wiki.qt.io/Main).

```shell
sudo apt install build-essential qt5-default qttools5-dev-tools
```

### Другие ОС

Смотрите [Qt Wiki](https://wiki.qt.io/Main).

## Сборка

Сборка in-source запрещена. Собирайте в новой директории:

```shell
mkdir build
cd build/
cmake ../
cmake --build .
```

# Пример

# Поддержка интернационализации

Шаблон включает поддержку интернационализации Qt.

Вам нужно только создать перевод, чтобы это заработало.

Обратите внимание, в данный момент модуль `utility_boilerplate_qt5` поддерживает только 2 языка:

1. Английский — встроен в исходный код
2. Русский

## Как собрать новый перевод?

ru_RU для примера, используйте ваш код языка.

1. Соберите все строки внутри `tr()` в TS файл с использованием `lupdate`.

   ```shell
   lupdate *.cpp -ts i18n/ru/app_ru.ts
   ```

2. Откройте в средстве переводов и переведите.

   ```shell
   linguist i18n/ru/app_ru.ts
   ```

3. Qt может загружать только один файл перевода за раз, поэтому необходимо создать полный перевод используя `lconvert`.
   Найдите файл содержащий локализацию системных строк Qt `qtbase_<language code>.ts` в пакете установки
   или [репозитории](https://github.com/qt/qttranslations/tree/dev/translations) и поместите его в
   директорию `i18n/<language code>`. Далее соберите TS файлы в один с помощью `lconvert`.

   ```shell
   cd i18n/
   lconvert -i ru/*.ts ../../utility_boilerplate_qt5/i18n/ru/*.ts -o ru/appcomp_ru.ts
   ```

4. Соберите QM файл используя `lrelease`. Система сборки автоматически копирует все QM файлы в директорию, где
   исполняемый файл может их найти.

   ```shell
   lrelease ru/appcomp_ru.ts ru/appcomp_ru.qm
   ```

5. Чтобы проверить, что перевод загружается корректно, запустите приложение из командной строки, и найдите
   строчку `Translation for "<language code>" load successfully`. Если перевод не загрузился вы
   увидите `Can't load translation for "<language code>"`. Qt не предлагает дополнительной отладочной информации.

# Контроль стиля кода

Проект предлагает инструменты контроля стиля кода с помощью clang-format and cmake-format. Включая стили для IDEA.

Проверка стиля в CI провалится, если хоть один файл не соответствует указанным правилам.

Установка инструментов контроля стиля необязательна.

## Установка зависимостей

### Windows

`clang-format` может быть [загружен](https://llvm.org/builds/) с пакетом LLVM.

`cmake-format` устанавливается с помощью `pip`.

```shell
pip install cmakelang pyyaml
```

### Linux

Должны иметь всё необходимое, кроме `cmake-format`.

```shell
pip install cmakelang
```

## Использование

Проверить все файлы в проекте.

```shell
cmake --build build --target check-format
```

Исправить все файлы в проекте.

```shell
cmake --build build --target fix-format
```
