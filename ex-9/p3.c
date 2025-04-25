#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function to find the LFU page index
int findLFUIndex(int frames[], int freq[], int frameCount) {
	int minFreq = freq[0], index = 0;

	for (int i = 1; i < frameCount; i++) {
		if (freq[i] < minFreq) {
			minFreq = freq[i];
			index = i;
		}
	}
	return index;
}

// Function to implement LFU page replacement
void lfuPageReplacement(int pages[], int pageCount, int frameCount) {
	int frames[MAX_FRAMES], freq[MAX_FRAMES] = {0};
	int pageFaults = 0, isPresent, index;

	// Initialize frames to -1 (indicating empty)
	for (int i = 0; i < frameCount; i++)
		frames[i] = -1;

	printf("\nPage Reference\tFrames\n");

	for (int i = 0; i < pageCount; i++) {
		isPresent = 0;

		// Check if the page is already in memory
		for (int j = 0; j < frameCount; j++) {
			if (frames[j] == pages[i]) {
				isPresent = 1;
				freq[j]++;  // Increase frequency count
				break;
			}
		}

		// Page fault if the page is not in memory
		if (!isPresent) {
			if (i < frameCount) {
				// Fill empty frames first
				frames[i] = pages[i];
				freq[i] = 1;
			} else {
				// Replace the least frequently used page
				index = findLFUIndex(frames, freq, frameCount);
				frames[index] = pages[i];
				freq[index] = 1; // Reset frequency for the new page
			}
			pageFaults++;
		}

		// Print the current memory state
		printf("%d\t\t", pages[i]);
		for (int j = 0; j < frameCount; j++) {
			if (frames[j] == -1)
				printf("_ ");
			else
				printf("%d ", frames[j]);
		}
		printf("\n");
	}

	printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
	int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
	int pageCount = sizeof(pages) / sizeof(pages[0]);
	int frameCount;

	printf("Enter the number of frames: ");
	scanf("%d", &frameCount);

	lfuPageReplacement(pages, pageCount, frameCount);

	return 0;
}


