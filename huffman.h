#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <memory>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

// Updated Node using Smart Pointers
struct Node
{
    char ch;
    int freq;
    std::shared_ptr<Node> left, right;
    Node(char c, int f)
        : ch(c)
        , freq(f)
        , left(nullptr)
        , right(nullptr)
    {}
};

struct Compare
{
    bool operator()(std::shared_ptr<Node> l, std::shared_ptr<Node> r) { return l->freq > r->freq; }
};

class Huffman
{
public:
    std::shared_ptr<Node> getRoot();
    struct Stats
    {
        long long originalSize = 0;
        long long compressedSize = 0;
        double ratio = 0.0;
    };

    bool compress(const std::string &inputPath, const std::string &outputPath);
    bool decompress(const std::string &inputPath,
                    const std::string &outputPath,
                    std::shared_ptr<Node> savedRoot);
    std::map<char, std::string> getCodes() { return huffmanCodes; }
    Stats getStats() { return lastStats; }


private:
    std::shared_ptr<Node> root;
    std::map<char, std::string> huffmanCodes;
    Stats lastStats;

    void generateCodes(std::shared_ptr<Node> node, std::string code);
};


#endif
