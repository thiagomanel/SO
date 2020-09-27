package prod_cons;

public class MainMonitor {
    private static int bufferSize = 5;
    private static int producerServiceTime = 100;
    private static int consumerServiceTime = 100;

    public static void main(String[] args) {
	// write your code here
        // creating buffer queue
        SharedBoundedStack buffer = new SharedBoundedStackMonitor(MainMonitor.bufferSize);
        Integer empty = new Integer(0);
        Integer full = new Integer(0);

        // starting consumer thread
        new OtherConsumer(buffer, MainMonitor.consumerServiceTime, full, empty);

        // starting producer thread
        new OtherProducer(buffer, MainMonitor.producerServiceTime, full, empty);
    }
}
