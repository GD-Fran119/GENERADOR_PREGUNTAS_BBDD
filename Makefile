#makefile

.PHONY: test
test: TEST

TEST: funciones.hpp main.cpp
	@echo "Compilando..."
	@g++ -std=gnu++14 $^ -o $@

.PHONY: clean
clean:
	@rm TEST
	@echo Borrado TEST

.PHONY: help
help:
	@echo
	@echo "TARGETS:"
	@echo "...test"
	@echo "...clean"
	@echo "...help"
	@echo