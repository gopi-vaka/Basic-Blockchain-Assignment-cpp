#include <iostream>
#include <vector>
#include <ctime>
#include "sha256.h" // Make sure sha256.h and sha256.cpp are in your project

using namespace std;

// Block structure
class Block {
public:
    int index;
    string previousHash;
    string hash;
    string data;
    time_t timestamp;
    int nonce;

    Block(int idx, string d, string prevHash = "")
        : index(idx), data(d), previousHash(prevHash), timestamp(time(0)), nonce(0) {
        hash = calculateHash();
    }

    string calculateHash() const {
        return sha256(to_string(index) + previousHash + to_string(timestamp) + data + to_string(nonce));
    }

    // Basic Proof of Work: finds hash with given difficulty (number of leading zeros)
    void mineBlock(int difficulty) {
        string target(difficulty, '0');
        while (hash.substr(0, difficulty) != target) {
            nonce++;
            hash = calculateHash();
        }
    }

    static Block mineBlock(const Block& prevBlock, const string& data, int difficulty = 4) {
        Block newBlock(prevBlock.index + 1, data, prevBlock.hash);
        newBlock.mineBlock(difficulty);
        return newBlock;
    }
};

// Validates entire blockchain
bool isChainValid(const vector<Block>& chain, int difficulty = 4) {
    string target(difficulty, '0');
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& current = chain[i];
        const Block& previous = chain[i - 1];

        if (current.hash != current.calculateHash()) return false;
        if (current.previousHash != previous.hash) return false;
        if (current.hash.substr(0, difficulty) != target) return false;
    }
    return true;
}

// Prints the blockchain
void printChain(const vector<Block>& chain) {
    for (const auto& block : chain) {
        cout << "Block #" << block.index << endl;
        cout << "Data: " << block.data << endl;
        cout << "Hash: " << block.hash << endl;
        cout << "Previous Hash: " << block.previousHash << endl;
        cout << "Nonce: " << block.nonce << endl;
        cout << "--------------------------" << endl;
    }
}

int main() {
    vector<Block> blockchain;

    // Creating the blockchain
    Block genesis(0, "A sends 10 BTC to B");
    genesis.mineBlock(4);
    blockchain.push_back(genesis);

    blockchain.push_back(Block::mineBlock(blockchain.back(), "B sends 5 BTC to C", 4));
    blockchain.push_back(Block::mineBlock(blockchain.back(), "C sends 2 BTC to D", 4));

    cout << "Blockchain before tampering:" << endl;
    printChain(blockchain);
    cout << "Is blockchain valid? " << (isChainValid(blockchain) ? "Yes" : "No") << endl;
    cout << endl;

    // Tampering with the second block
    blockchain[1].data = "B sends 50 BTC to C"; // Tampered
    blockchain[1].hash = blockchain[1].calculateHash(); // Recalculate tampered hash

    cout << "Blockchain after tampering:" << endl;
    printChain(blockchain);
    cout << "Is blockchain valid? " << (isChainValid(blockchain) ? "Yes" : "No") << endl;

    return 0;
}