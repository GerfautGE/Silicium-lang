#include <iostream>
#include <string>
#include <vector>

#include "ast.h"

enum class NodeType {
    NodeList,
    IntLeaf,
    StringLeaf,
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
        NodeType getType() const override {return NodeType::IntLeaf; }

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
        NodeListNode(Tag tag, std::vector<ASTNode*> list) : tag(tag){}
        NodeType getType() const override { return NodeType::NodeList; }

        Tag getTag() const { return tag; }
        void addNode(ASTNode* node) { list.push_back(node); }
        const std::vector<ASTNode*>* getList() const { return &list; }
    private:
        Tag tag;
        std::vector<ASTNode*> list;
};

class StringNode : public ASTNode {
        public:
            StringNode(std::string value) : value(value) {}
            NodeType getType() const override { return NodeType::StringLeaf; }

            std::string getValue() const { return value; }
        private:
            std::string value;
};

void dotAST(const ASTNode* node, int depth = 0) {
    if(node) {
        std::string indent(depth, ' ');
        std::cout << indent;
        switch (node->getType())
        {
        case NodeType::IntLeaf:
            std::cout << "Literal : " << static_cast<const LiteralNode*>(node)->getValue() << std::endl;
            break;
        case NodeType::BinaryOp:
            std::cout << "BinaryOp : " << static_cast<const BinaryOpNode*> (node)->getOperator() << std::endl;
            dotAST(static_cast<const BinaryOpNode*> (node)->getLeft(), depth + 2);
            dotAST(static_cast<const BinaryOpNode*> (node)->getRight(), depth + 2);
            break;
        case NodeType::NodeList:
            std::cout << "Node : " << tag_to_string(static_cast<const NodeListNode*> (node)->getTag()) << std::endl;
            for(ASTNode* child : *static_cast<const NodeListNode*> (node)->getList()) {
                dotAST(child, depth + 2);
            }
        case NodeType::StringLeaf:
            std::cout << "String : " << static_cast<const StringNode*> (node)->getValue() << std::endl;
            break;
        }
    }
}

int main() {
    ASTNode* root = {new NodeListNode(
        Tag::Tlistglobdef,
        { new StringNode("main"), new LiteralNode(3)}
        )};

    dotAST(root);

    delete root;

    return 0;
}
