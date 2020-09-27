package prod_cons;

public class OtherConsumer implements Runnable {
    private SharedBoundedStackMonitor buffer;
    private int serviceTime;
    private Integer full;
    private Integer empty;

    OtherConsumer(SharedBoundedStack b, int serviceTime, Integer full, Integer empty)
    {
        this.buffer = (SharedBoundedStackMonitor) b;
        this.serviceTime = serviceTime;
        this.full = full;
        this.empty = empty;
        new Thread((Runnable) this, "Consumer").start();
    }

    public void run()
    {
        int item;
        while(true) {
            synchronized (this.empty) {
                while (this.buffer.getStackPointer() == 0) {
                    try {
                        this.empty.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }

            // consumer get items
            item = buffer.get();
            // the sleep simulates the time to consume an item
            try {
                Thread.sleep(this.serviceTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(String.format("Consumer has consumed %d", item));

            synchronized (this.full) {
                this.full.notify();
            }
        }
    }
}
