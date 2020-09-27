package prod_cons;

public class MainSemaphore {
    private static int bufferSize = 5;
    private static int producerServiceTime = 100;
    private static int consumerServiceTime = 100;

    public static void main(String[] args) {
	// write your code here
        // creating buffer queue
        SharedBoundedStack buffer = new SharedBoundedStackSemaphore(MainSemaphore.bufferSize);

        // starting consumer thread
        new Consumer(buffer, MainSemaphore.consumerServiceTime);

        // starting producer thread
        new Producer(buffer, MainSemaphore.producerServiceTime);
    }
}
