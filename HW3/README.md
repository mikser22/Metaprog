# С++ Библиотека для работы с графами 

Подробное описание задания [здесь](https://docs.google.com/document/d/1EtUDwvB0wuBCXp9rCkeQBZAdxo_kaZT2Jw00dFMaZPA/edit)

## Описание и стандартные возможности

Создание графов и работа с ними. В качестве вершин и весов рёбер графа могут выступать абсолютно разные сущности -- начиная от обычных чисел и заканчивая большими программными модулями 

#### Возможности:

1. Создание графа по матрице смежности
2. Итерация по вершинам с выполнением некоторого действия
3. Генерация структуры графа на этапе компиляции (например, для графа сервисов в системе)

    * Для этого необходимо задавать типы вершин и ребер при создании Графа. В дальнейшем изменить кол-во и тип вершин/ребер будет невозможно

## Быстрый старт

Создать граф можно с помощью следующей конструкции
``` 
Graph<
		TypeList<
			Cat, Dog, CatDog // Типы вершин
		>,
		TypeList< // Типы ребер
			int, int, char,    // (0, 0) (0, 1) (0, 2)
			int, int, float,   // (1, 0) (1, 1) (1, 2)
			double, short, int // (2, 0) (2, 1) (2, 2)
		>,
		false> graph;
```
Имеет три параметра:

1. Тайплист типов вершин. 
2. Тайплист типов ребер. Должен именять размер `size * size`, где `size` это голичество вершин. Ребро `(i, j)` стоит на месте `i * size + j`
3. Флаг ориентированности графа. `true` если ориентированный


Задать значения `val` вершине по индексу `ind` можно с помощью метода `AddVertex<ind>(val)`
<br> Например:
``` 
graph.AddVertex<1>(dog);
```
 
 ``` 
 Graph<
		TypeList<
			Cat, Dog, CatDog // Типы вершин
		>,
		TypeList< // Типы ребер
			int, int, char,    // (0, 0) (0, 1) (0, 2)
			int, int, float,   // (1, 0) (1, 1) (1, 2)
			double, short, int // (2, 0) (2, 1) (2, 2)
		>,
		false> graph;

	Cat cat;
	Dog dog;
	CatDog cd;
	graph.AddVertex<1>(dog);
	graph.AddVertex<0>(cat);
	graph.AddVertex<2>(cd);
 ```
 
Задать значения `val` ребру `(i, j)` можно с помощью метода `AddEdge<i, j>(val)`
<br> Например:
``` 
graph.AddEdge<0, 0>(228);
```

### Итерация по вершинам и выполнение действия

Для итерации по вершинам графа необходимо создать структуру, в которой реализованы функции `void vertexFunction(int index, const std::unique_ptr<Type>& vertex)` для каждого типа вершины `Type`

Например:
``` 
struct DispatchFunctions
{
	void vertexFunction(int index, const std::unique_ptr<Cat>& vertex)
	{
		for (int i = 0; i <= index; ++i) {
			std::cout << "MEOW \n";
		};
		std::cout << std::endl;
	}

	void vertexFunction(int index, const std::unique_ptr<Dog>& vertex)
	{
		for (int i = 0; i <= index; ++i) {
			std::cout << "BARK \n";
		};
		std::cout << std::endl;
	}

	void vertexFunction(int index, const std::unique_ptr<CatDog>& vertex)
	{
		for (int i = 0; i <= index; ++i) {
			std::cout << "MEOW or BARK\n";
		};
		std::cout << std::endl;
	}
};
```

Далее вызвав `graph.dispatch(DispatchFunctions())` Произойдет итерации по всем вершинам с вызовом соответствующих функций.

К примеру данный кусок кода с объявленными выше функциями

```
Graph<
		TypeList<
			Cat, Dog, CatDog // Типы вершин
		>,
		TypeList< // Типы ребер
			int, int, char,    // (0, 0) (0, 1) (0, 2)
			int, int, float,   // (1, 0) (1, 1) (1, 2)
			double, short, int // (2, 0) (2, 1) (2, 2)
		>,
		false> graph;

	Cat cat;
	Dog dog;
	CatDog cd;
	graph.AddVertex<1>(dog);
	graph.AddVertex<0>(cat);
	graph.AddVertex<2>(cd);

	
	graph.dispatch(DispatchFunctions());
```

Выведет в консоль:
```
MEOW

BARK
BARK

MEOW or BARK
MEOW or BARK
MEOW or BARK
```