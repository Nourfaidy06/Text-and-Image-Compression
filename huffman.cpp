#include "huffman.h"
#include <fstream>
#include <queue>

// Recursive function to traverse the tree and assign 0s and 1s
void Huffman::generateCodes(std::shared_ptr<Node> node, std::string code)
{
    if (!node)
        return;

    // If it's a leaf node, save the character and its code
    if (!node->left && !node->right) {
        huffmanCodes[node->ch] = code;
    }

    generateCodes(node->left, code + "0");
    generateCodes(node->right, code + "1");
}

bool Huffman::compress(const std::string &inputPath, const std::string &outputPath)
{
    // Read File in binary mode
    std::ifstream inFile(inputPath, std::ios::binary);
    if (!inFile)
        return false;

    std::string text((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    if (text.empty())
        return false;

    // 1. Frequency Map: Count how many times each character appears
    std::unordered_map<char, int> freq;
    for (char c : text)
        freq[c]++;

    // 2. Build Tree using a Priority Queue (Min-Heap)
    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, Compare> pq;
    for (auto p : freq) {
        pq.push(std::make_shared<Node>(p.first, p.second));
    }

    while (pq.size() > 1) {
        auto l = pq.top();
        pq.pop();
        auto r = pq.top();
        pq.pop();

        // Create internal node with the sum of frequencies
        auto parent = std::make_shared<Node>('\0', l->freq + r->freq);
        parent->left = l;
        parent->right = r;
        pq.push(parent);
    }
    root = pq.top();

    // 3. Generate the dictionary of Huffman Codes
    huffmanCodes.clear();
    generateCodes(root, "");

    // 4. Encode the text and save to file
    std::string encoded = "";
    for (char c : text) {
        encoded += huffmanCodes[c];
    }

    std::ofstream outFile(outputPath);
    if (!outFile)
        return false;
    outFile << encoded;
    outFile.close();

    // 5. Calculate statistics for the GUI display
    lastStats.originalSize = (long long) text.length() * 8;  // bits
    lastStats.compressedSize = (long long) encoded.length(); // bits
    if (lastStats.originalSize > 0) {
        lastStats.ratio = (1.0 - (double) lastStats.compressedSize / lastStats.originalSize)
                          * 100.0;
    }

    return true;
}

// Added this to prevent "undefined reference" errors if your header mentions it

bool Huffman::decompress(const std::string& inputPath, const std::string& outputPath, std::shared_ptr<Node> savedRoot) {
    // Read encoded file
    std::ifstream inFile(inputPath);
    if (!inFile) return false;

    std::string encoded((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    if (encoded.empty()) return false;

    // Use saved Huffman tree root
    std::shared_ptr<Node> curr = savedRoot;
    std::string decoded = "";

    for (char bit : encoded) {
        curr = (bit == '0') ? curr->left : curr->right;

        // Leaf node reached
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = savedRoot;
        }
    }

    // Write decoded text to file
    std::ofstream outFile(outputPath);
    if (!outFile) return false;
    outFile << decoded;
    outFile.close();

    return true;
}
std::shared_ptr<Node> Huffman::getRoot()
{
    return root;
}