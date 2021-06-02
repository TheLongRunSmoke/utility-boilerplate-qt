English | [Русский](README.ru.MD)

[![Qt5 Utility Boilerplate by TheLongRunSmoke]()](#)

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

**Translations support**

How to assemble new translation, on ru_RU example.

Use lupdate *.cpp -ts i18n/ru/app_ru.ts to collect strings to translate.

Use linguist i18n/ru/app_ru.ts to load it in to translation tool.

Next you need to collect complete translation file unsung lconvert.

cd i18n/

lconvert -i ru/app_ru.ts ../utility_boilerplate_qt5/i18n/ru/*.ts -o ru/appcomp_ru.ts

Convert translation file to qm file, that Qt can load, with lrelease.
lrelease ru/appcomp_ru.ts ru/appcomp_ru.qm