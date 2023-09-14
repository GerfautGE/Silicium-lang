#include <iostream>
#include <string>
#include <vector>

#include "ast.h"

enum class NodeType {
    NodeList,
    Int,
    BinaryOp,
};

class ASTNode
{
    public:
        virtual ~ASTNode() {}
        virtual NodeType getType() const = 0;
};

class LiteralNode : public ASTNode {
    public:
        LiteralNode(int value) : value{value} {}
        NodeType getType() const override {return NodeType::Int; }

        int getValue() const {return value; }

        private:
            int value;
};

class BinaryOpNode : public ASTNode {
    public:
        BinaryOpNode(Tag tag, ASTNode* left, ASTNode* right) : tag(tag), left(left), right(right) {}
        NodeType getType() const override { return NodeType::BinaryOp; }

        std::string getOperator() const { return tag_to_string(tag); }
        ASTNode* getLeft() const { return left; }
        ASTNode* getRight() const {return right; }

    private:
        Tag tag;
        ASTNode* left;
        ASTNode* right;
};

class NodeListNode : public ASTNode {
    public:
        NodeListNode(Tag tag, ASTNode** list) : tag(tag){}
        NodeType getType() const override { return NodeType::NodeList; }

        Tag getTag() const { return tag; }
        void addNode(ASTNode* node) { list.push_back(node); }
        const std::vector<ASTNode*>* getList() { return &list; }
    private:
        Tag tag;
        std::vector<ASTNode*> list;
};

void dotAST(const ASTNode* node, int depth = 0) {
    if(node) {
        std::string indent(depth, ' ');
        std::cout << indent;
        switch (node->getType())
        {
        case NodeType::Int:
            std::cout << "Literal : " << static_cast<const LiteralNode*>(node)->getValue() << std::endl;
            break;
        case NodeType::BinaryOp:
            std::cout << "BinaryOp : " << static_cast<const BinaryOpNode*> (node)->getOperator() << std::endl;
            dotAST(static_cast<const BinaryOpNode*> (node)->getLeft(), depth + 2);
            dotAST(static_cast<const BinaryOpNode*> (node)->getRight(), depth + 2);
            break;
        case NodeType::NodeList:
            std::cout << "Node : " << tag_to_string(static_cast<const NodeListNode*> (node)->getTag()) << std::endl;
        }
    }
}

int main() {
    ASTNode* root = {new NodeListNode(
        Tag::Tlistglobdef,
        {}
    )};

    dotAST(root);

    delete root;

    return 0;
}