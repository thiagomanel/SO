package prod_cons.semaphore;

public class Main {
    private static int bufferSize = 10;
    private static int producerServiceTime = 100;
    private static int consumerServiceTime = 100;

    public static void main(String[] args) {
	// write your code here
        // creating buffer queue
        SharedBuffer buffer = new SharedBuffer(Main.bufferSize);

        // starting consumer thread
        new Consumer(buffer, Main.consumerServiceTime);

        // starting producer thread
        new Producer(buffer, Main.producerServiceTime);
    }
}
