package prod_cons;

public class MainMonitorIncomplete {
    private static int bufferSize = 10;
    private static int producerServiceTime = 500;
    private static int consumerServiceTime = 100;

    public static void main(String[] args) {
	// write your code here
        // creating buffer queue
        SharedBoundedStack buffer = new SharedBoundedStackMonitorIncomplete(MainMonitorIncomplete.bufferSize);

        // starting consumer thread
        new Consumer(buffer, MainMonitorIncomplete.consumerServiceTime);

        // starting producer thread
        new Producer(buffer, MainMonitorIncomplete.producerServiceTime);
    }
}
