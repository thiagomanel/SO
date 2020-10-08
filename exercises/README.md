# API threads
```
// cria uma nova thread, que será apontada por t. A thread criada executará
// a função apontada por function_ptr. Ao fim da execução, a thread que foi
// criada já está pronta para ser executada pelo escalonador.
void create (thread* t, function_ptr*)

// esta função permite que a thread que a chamou indique o fim de sua
// execução
void exit ()

// esta função permite bloquear a thread que a chama até que uma outra
// target_thread termine sua execução. Caso a target_thread já tenha
// terminado sua execução antes da chamada para join, a chamada para join
// não irá bloquear.
void join (thread target_thread)

// para implementar as funções acima, você pode considerar o uso das
// seguintes funções auxiliares

// esta função retorna a thread que executa atualmente
thread current_thread()

// Toda thread tem um identificador inteiro único. Esta função retorna o
// valor deste identificador para a thread t
int get_tid(thread t)
```

# API Barreira

```
// Constrói um objeto Barreira de tamanho size
Barreira (int size)

// Espera até que um número suficiente de fluxos tenham chamado wait()
void wait ()
```
