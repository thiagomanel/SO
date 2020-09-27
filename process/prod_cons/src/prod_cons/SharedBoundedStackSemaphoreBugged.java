package prod_cons;

import java.util.concurrent.Semaphore;

public class SharedBoundedStackSemaphoreBugged implements SharedBoundedStack {
    // size of the shared buffer
    private int stackSize;
    // shared buffer
    private int[] stack;
    // points to the top of the stack; 0 means that the stack is empty
    private int stackPointer;
    // "mutex" ensures that access to the shared stack does not lead to a race condition
    private Semaphore mutex;
    // "empty" blocks the Consumer when the stack is empty; the shared stack is initially empty.
    private Semaphore empty;
    // "full" blocks the producer when there is no space left in the shared stack.
    private Semaphore full;

    public SharedBoundedStackSemaphoreBugged(int stackSize) {
        this.stackSize = stackSize;
        this.stack = new int[this.stackSize];
        this.stackPointer = 0;
        this.mutex = new Semaphore(1);
        this.empty = new Semaphore(0);
        this.full = new Semaphore(this.stackSize);
    }

    // to get an item from buffer
    public int get()
    {
        int ret;

        try {
            // Before a consumer can consume an item, it must acquire a permit from mutex to enter the critical region
            this.mutex.acquire();
        }
        catch (InterruptedException e) {
            System.out.println("InterruptedException caught");
        }

        try {
            // Before a consumer can consume an item, it must make sure there is an item to be consumed
            this.empty.acquire();
        }
        catch (InterruptedException e) {
            System.out.println("InterruptedException caught");
        }

        ret = this.stack[--this.stackPointer];
        System.out.println(String.format("Consumer has removed %d from slot %d", ret, this.stackPointer));

        // After a consumer consumes an item, it releases mutex to allow others to enter the critical region
        this.mutex.release();
        // After a consumer consumes an item, it releases full to notify the provider that there is a new free slot
        this.full.release();

        return ret;
    }

    // to put an item in buffer
    public void put(int item)
    {
        try {
            // Before a producer can produce an item, it must make sure there is a free slot to add the new item
            this.full.acquire();
        }
        catch (InterruptedException e) {
            System.out.println("InterruptedException caught");
        }
        try {
            // Before a producer can produce an item, it must acquire a permit from mutex to enter the critical region
            this.mutex.acquire();
        }
        catch (InterruptedException e) {
            System.out.println("InterruptedException caught");
        }

        System.out.println(String.format("Producer has inserted %d in slot %d", item, this.stackPointer));
        this.stack[this.stackPointer++] = item;

        // After a producer produces an item, it releases mutex to allow others to enter the critical region
        this.mutex.release();
        // After a producer produces an item, it releases empty to notify the consumer that there is a new item to consume
        this.empty.release();
    }
}
