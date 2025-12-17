#include "redblacktree.h"
int main() {
    // 测试1：创建示例中的树 12-10-5
    cout << "测试1：创建树 12-10-5\n";
    RedBlackTree tree1;
    tree1.insert(12);
    tree1.insert(10);
    tree1.insert(5);
    tree1.showSimple();

    // 测试2：更复杂的树
    cout << "\n\n测试2：创建更复杂的树\n";
    RedBlackTree tree2;

    vector<int> values = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85 };

    cout << "插入值: ";
    for (int val : values) {
        cout << val << " ";
        tree2.insert(val);
    }
    cout << "\n\n";
    tree2.showInfo();
    tree2.showLevelOrder();
    tree2.showSimple();
	tree2.deleteNode(20);
	std::cout << "\n删除节点 20 后的树结构:\n";
	tree2.showSimple();
	tree2.clear_tree();
	cout << "\n清空树后:\n";
	tree2.showSimple();
    // 测试3：不平衡的树
    std::cout << "\n\n测试3：测试右斜树\n";
    RedBlackTree tree3;
    for (int i = 1; i <= 10; i++) {
        tree3.insert(i);
    }

    tree3.showSimple();

    // 测试4：测试搜索功能
    std::cout << "\n\n测试4：搜索测试\n";
    int searchKey = 40;
    auto result = tree2.search(searchKey);
    if (result) {
        std::cout << "找到节点 " << searchKey << "，颜色: "
            << (result->color ? "红色(R)" : "黑色(B)") << std::endl;
    }
    else {
        std::cout << "未找到节点 " << searchKey << std::endl;
    }

    return 0;
}