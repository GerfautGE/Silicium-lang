#pragma once
#include <string>
#include <vector>

extern "C" int yylex();
extern "C" FILE* yyin;

enum class Tag {
    Tfundef,
    Tfuname,
    Tfunargs,
    Tfunboby,
    Tret,
    Tnum,
    Tlistglobdef,
};

static std::string tag_to_string(Tag tag) {
    switch (tag)
    {
    case Tag::Tfundef:
        return std::string("Tfundef");
    case Tag::Tfuname:
        return std::string("Tfuname"); 
    case Tag::Tfunargs:
        return std::string("Tfunargs");   
    case Tag::Tfunboby:
        return std::string("Tfunbody");
    case Tag::Tret:
        return std::string("Tret");
    case Tag::Tnum:
        return std::string("Tnum");
    case Tag::Tlistglobdef:
        return std::string("Tlistglobdef");
    default:
        return std::string("Unknown");
    }
};


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




ASTNode * buildAST();
void dotAST(ASTNode*, int);
