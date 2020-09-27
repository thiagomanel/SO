package prod_cons;

public class SharedBoundedStackMonitorIncomplete implements SharedBoundedStack {
    // size of the shared buffer
    private int stackSize;
    // shared buffer
    private int[] stack;
    // points to the top of the stack; 0 means that the stack is empty
    private int stackPointer;

    public SharedBoundedStackMonitorIncomplete(int stackSize) {
        this.stackSize = stackSize;
        this.stack = new int[this.stackSize];
        this.stackPointer = 0;
    }

    // to get an item from buffer
    synchronized public int get()
    {
        int ret;

        ret = this.stack[--this.stackPointer];
        System.out.println(String.format("Consumer has removed %d from slot %d", ret, this.stackPointer));

        return ret;
    }

    // to put an item in buffer
    synchronized public void put(int item)
    {
        System.out.println(String.format("Producer has inserted %d in slot %d", item, this.stackPointer));
        this.stack[this.stackPointer++] = item;
    }
}
