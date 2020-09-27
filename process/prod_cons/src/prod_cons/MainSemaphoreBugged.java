package prod_cons;

public class MainSemaphoreBugged {
    private static int bufferSize = 5;
    private static int producerServiceTime = 100;
    private static int consumerServiceTime = 100;

    public static void main(String[] args) {
	// write your code here
        // creating buffer queue
        SharedBoundedStack buffer = new SharedBoundedStackSemaphoreBugged(MainSemaphoreBugged.bufferSize);

        // starting consumer thread
        new Consumer(buffer, MainSemaphoreBugged.consumerServiceTime);

        // starting producer thread
        new Producer(buffer, MainSemaphoreBugged.producerServiceTime);
    }
}
