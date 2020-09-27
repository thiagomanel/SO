package prod_cons;

public class OtherProducer implements Runnable {
    private SharedBoundedStackMonitor buffer;
    private int serviceTime;
    private Integer full;
    private Integer empty;

    OtherProducer(SharedBoundedStack b, int serviceTime, Integer full, Integer empty)
    {
        this.buffer = (SharedBoundedStackMonitor) b;
        this.serviceTime = serviceTime;
        this.full = full;
        this.empty = empty;
        new Thread((Runnable) this, "Producer").start();
    }

    public void run()
    {
        int i = 1;
        while (true) {
            synchronized (this.full) {
                while (this.buffer.getStackPointer() == this.buffer.getStackSize()) {
                    try {
                        this.full.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }

            // producer producing an item; the sleep just simulates the time to produce
            try {
                Thread.sleep(this.serviceTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            // producer put items
            System.out.println(String.format("Producer has produced %d", i));
            this.buffer.put(i++);

            synchronized (this.empty) {
                this.empty.notify();
            }
        }
    }
}
