# Лабораторная работа № 3

Подготовить в репозитории ветку `lab3` и создать `merge request` в ветку `master`.

Подготовить программный код в папке `src`:

1. Программная реализация компонента бизнес-логики c базовым покрытием `Unit`-тестами (увлекаться не стоит, покройте самые важные части).

---

* Фреймворк для юнит-тестов: `GoogleTest`.

Реализована большая часть бизнес-логики.

## Семантическое деление исходников по директориям:
* `src/model` - сущности бизнес-логики
* `src/core` - классы реализующие бизнес-логику
* `src/tools` - полезные утилиты (логгер) не вошедшие в `core`
* `unit_tests/mock` - моки для интерфейсов
* `unit_tests/core` - юнит-тесты бизнес-логики
