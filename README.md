# LRUCache

En la solución implementada en c++ uso un `unordered_map` y una estructura adicional llamada `node`. Cada pair del map es el input `key` como su key y el segundo valor es un puntero a la estructura `node`. También se crearon cuatro variables privadas que almacenan el `size` del cache, el `counter` de la cantidad actual de pairs, el key del root y el key del tail.
```
unordered_map <input_key, node *>
```
Todas las operaciones básicas (`insert`, `getRecent`, `getValue`) corren en tiempo costante gracias a las funciones auxiliares del `unordered_map`.
### Estructura de `node`
La estructura adicional contiene el valor de input `value` y dos variales adicionales que contienen solo el key de el dato anterior y el siguiente. Esta implementación trata de imitar a una doubly linked list, no se guardo un puntero al siguiente pair del `unordered_map` debido a que su función `find()` nos evita crear iteradores dentro de nuestra clase, esta operación no aumenta el tiempo de ejecución.o
```
node {
  value
  next_key
  prev_key
}
```

## Funciones implementadas
### `insertKeyValuePair`
En la función evaluo cuatros casos principales: el caso base (el map esta vacio), cuando el LRU cache esta lleno (la cantidad de pairs es igual o mayor al `size` del cache), ya existe el key (se necesita hacer un update del valor) y una simple inserción de un nuevo pair. Por cada simple inserción se actualiza la variable `tail_key` con el nuevo `key`.
```
node *new_node = new node(value); // creo un nuevo node con el valor dado
cache.insert({key, new_node}); // inserto el pair en el map. O(1)
		
auto aux = cache.find(key); // almaceno el pair en una variable auxiliar
		
aux->second->prev_key = tail->first; // guardo el tail_key como el prev_key del nuevo nodo
tail->second->next_key = key; // guardo el nuevo key como el next_key del pair tail

tail_key = key; // actualizo el key del tail pair
```

### `getMostRecentKey`
Debido a que se esta untilizando el `unordered_map` solo utilizamos la función auxiliar `find()` y pasamos como parametro nuestro `tail_key`.
```
auto tail = cache.find(tail_key); // encontramos el pair. O(1)
std::cout << tail->first << std::endl; // lo imprimimos
```

### `getValueFromKey`
Igual que en la función anterior, se hace uso de la función auxiliar `find()` pero esta vez como parametro el parametro de la función. Existe un caso a tener en cuenta, cuando se llama a esta pero la key no esta dentro del cache.
```
auto found = cache.find(key);

if (found == cache.end()) { // cuando la key no se encuentra en el cache. O(1)
	std::cout << "not found" << std::endl;
	return false;		
}
```
Cada vez que se llame a esta función se necesita actualizar nuestro tail, debido a que el pair buscado seria nuestro most recently used key. En este caso el uso de una doubly linked list nos favorece para actualizar el orden del cache.
```
auto aux_p = cache.find(found->second->prev_key);  // O(1)
auto aux_n = cache.find(found->second->next_key);  // O(1)

aux_p->second->next_key = aux_n->first; // cambio el valor del next_key del pair anterior al buscado con el siguiente a este
aux_n->second->prev_key = aux_p->first;

// el pair encontrado se vuelve nuestro nuevo tail 
tail->second->next_key = found->first;
found->second->prev_key = tail->first;
tail_key = key;
```
