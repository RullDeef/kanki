# Лабораторный практикум по ППО

Отчеты по лабораторным работам:

* [Лабораторная работа №1](docs/readme1.md)
* [Лабораторная работа №2](docs/readme2.md)
* [Лабораторная работа №3](docs/readme3.md)

---

### Запуск CLI для редиса из контейнера:

```shell
docker run -it --network host --rm redis:7-alpine redis-cli
```

### Запуск локального раннера для дебага workflow

```shell
act -P ubuntu-latest=danger89/cmake
```
