package prod_cons;

public class Consumer implements Runnable {
    private SharedBoundedStack buffer;
    private int serviceTime;

    Consumer(SharedBoundedStack b, int serviceTime)
    {
        this.buffer = b;
        this.serviceTime = serviceTime;
        new Thread((Runnable) this, "Consumer").start();
    }

    public void run()
    {
        int item;
        while(true) {
            // consumer get items
            item = buffer.get();
            // the sleep simulates the time to consume an item
            try {
                Thread.sleep(this.serviceTime);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(String.format("Consumer has consumed %d", item));
        }
    }
}
