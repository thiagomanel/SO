package prod_cons.semaphore;

import java.util.concurrent.Semaphore;

public class SharedBuffer {
    // size of the shared buffer
    private int bufferSize;
    // shared buffer
    private int[] buffer;
    // points to the next slot where an item should be inserted
    private int input_pointer;
    // points to the next slot from where an item should be removed
    private int output_pointer;
    // "mutex" ensures that access to the shared buffer
    // does not lead to a race condition
    private Semaphore mutex;
    // "empty" blocks the Consumer when the buffer is empty
    // the shared buffer is initially empty.
    private Semaphore empty;
    // "full" blocks the producer when there is no space left
    // in the shared buffer.
    private Semaphore full;

    public SharedBuffer(int bufferSize) {
        this.bufferSize = bufferSize;
        this.buffer = new int[this.bufferSize];
        this.input_pointer = 0;
        this.output_pointer = 0;
        this.mutex = new Semaphore(1);
        this.empty = new Semaphore(0);
        this.full = new Semaphore(this.bufferSize);
    }

    // to get an item from buffer
    int get()
    {
        int ret;

        try {
            this.empty.acquire();
        }
        catch (InterruptedException e) {
            System.out.println("InterruptedException caught");
        }

        try {
            // Before a consumer can consume an item, it must acquire a permit from mutex to enter the critical region
            this.mutex.acquire();
        }
        catch (InterruptedException e) {
            System.out.println("InterruptedException caught");
        }

        ret = this.buffer[this.output_pointer];
        System.out.println(String.format("Consumer has removed %d from slot %d", ret, this.output_pointer));
        this.output_pointer = (this.output_pointer+1) % this.bufferSize;

        // After a consumer consumes an item, it releases mutex to allow others to enter the critical region
        this.mutex.release();
        // After a consumer consumes an item, it releases full to notify the provider that there is a new free slot
        this.full.release();

        return ret;
    }

    // to put an item in buffer
    void put(int item)
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

        this.buffer[this.input_pointer] = item;
        System.out.println(String.format("Producer has inserted %d in slot %d", item, this.input_pointer));
        this.input_pointer = (this.input_pointer+1) % this.bufferSize;

        // After a producer produces an item, it releases mutex to allow others to enter the critical region
        this.mutex.release();
        // After a producer produces an item, it releases empty to notify the consumer that there is a new item to consume
        this.empty.release();
    }
}
