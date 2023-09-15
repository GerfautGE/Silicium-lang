#include <iostream>
#include <string>
#include <vector>

#include "ast.hpp"

void dotAST(ASTNode* node, int depth) {
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
        default:
            std::cout << "Unknown node type" << std::endl;
            break;
        }
    }
}

