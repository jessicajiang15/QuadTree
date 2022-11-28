#include "QuadTree.h"
//A quad tree

QuadTree::QuadTree(Rectangle *s, double minX, double maxX, double minY, double maxY)
{
    this->root = new Node(s);
    root->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
}
QuadTree::QuadTree()
{
    root = nullptr;
}
int QuadTree::size(Node *n)
{
    int count = 1;
    if (n->isLeaf())
    {
        return 1;
    }
    vector<Node *> children;
    children = n->getChildren();
    int t1 = size(children[0]);
    int t2 = size(children[1]);
    int t3 = size(children[2]);
    int t4 = size(children[3]);

    return count + t1 + t2 + t3 + t4;
}
/*
    check for accuracy
    */
vector<Node *> QuadTree::getNodes(Node *n)
{
    vector<Node *> temp;
    if (n->isLeaf())
    {
        return temp;
    }
    else
    {
        temp.push_back(n);
    }

    vector<Node *> children;
    children = n->getChildren();
    vector<Node *> t1 = asVector(children[0]);
    vector<Node *> t2 = asVector(children[1]);
    vector<Node *> t3 = asVector(children[2]);
    vector<Node *> t4 = asVector(children[3]);

    temp.insert(temp.end(), t1.begin(), t1.end());
    temp.insert(temp.end(), t2.begin(), t2.end());
    temp.insert(temp.end(), t3.begin(), t3.end());
    temp.insert(temp.end(), t4.begin(), t4.end());

    return temp;
}
vector<Node *> QuadTree::getLeaves(Node *n)
{
    vector<Node *> temp;
    if (n->isLeaf())
    {
        temp.push_back(n);
        return temp;
    }

    vector<Node *> children;
    children = n->getChildren();
    vector<Node *> t1 = asVector(children[0]);
    vector<Node *> t2 = asVector(children[1]);
    vector<Node *> t3 = asVector(children[2]);
    vector<Node *> t4 = asVector(children[3]);

    temp.insert(temp.end(), t1.begin(), t1.end());
    temp.insert(temp.end(), t2.begin(), t2.end());
    temp.insert(temp.end(), t3.begin(), t3.end());
    temp.insert(temp.end(), t4.begin(), t4.end());

    return temp;
}

vector<Node *> QuadTree::asVector(Node *n)
{
    vector<Node *> temp;
    temp.push_back(n);
    if (n->isLeaf())
    {
        return temp;
    }

    vector<Node *> children;
    children = n->getChildren();
    vector<Node *> t1 = asVector(children[0]);
    vector<Node *> t2 = asVector(children[1]);
    vector<Node *> t3 = asVector(children[2]);
    vector<Node *> t4 = asVector(children[3]);

    temp.insert(temp.end(), t1.begin(), t1.end());
    temp.insert(temp.end(), t2.begin(), t2.end());
    temp.insert(temp.end(), t3.begin(), t3.end());
    temp.insert(temp.end(), t4.begin(), t4.end());

    return temp;
}

int QuadTree::thisSize()
{
    return QuadTree::size(this->getRoot());
}

Node *QuadTree::getRoot()
{
    return this->root;
}

void QuadTree::setRoot(Rectangle *s)
{
    this->root = new Node(s);
}

void QuadTree::divide(double minX, double maxX, double minY, double maxY, Function *F, Node *n, double tol, int maximumLevel)
{
    if (abs(n->getRekt()->integrate(F) - n->getRekt()->approx(F)) > tol && n->getLevel() <= maximumLevel)
    {
        n->createChildren();
        vector<Node *> children = n->getChildren();
        divide(minX, maxX, minY, maxY, F, children[0], tol, maximumLevel);
        divide(minX, maxX, minY, maxY, F, children[1], tol, maximumLevel);
        divide(minX, maxX, minY, maxY, F, children[2], tol, maximumLevel);
        divide(minX, maxX, minY, maxY, F, children[3], tol, maximumLevel);
    }
    else
    {
        n->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        return;
    }
}

void QuadTree::divideTree(double minX, double maxX, double minY, double maxY, Function *F, double tol, int maximumLevel)
{
    QuadTree::divide(minX, maxX, minY, maxY, F, this->root, tol, maximumLevel);
}

vector<Rectangle *> QuadTree::getOutBoxes(Node *n, Function *F, double cutoff)
{
    vector<Rectangle *> temp;
    if (n->isLeaf())
    {
        double integral = n->integrate(F);
        if (integral != -1)
        {
            if (integral > scaleCutoff(cutoff, n->getLevel()))
            {
                temp.push_back(n->getRekt());
                return temp;
            }
        }
    }
    vector<Node *> children = n->getChildren();
    vector<Rectangle *> r1 = getOutBoxes(children[0], F, cutoff);
    vector<Rectangle *> r2 = getOutBoxes(children[1], F, cutoff);
    vector<Rectangle *> r3 = getOutBoxes(children[2], F, cutoff);
    vector<Rectangle *> r4 = getOutBoxes(children[3], F, cutoff);
    temp.insert(temp.end(), r1.begin(), r1.end());
    temp.insert(temp.end(), r2.begin(), r2.end());
    temp.insert(temp.end(), r3.begin(), r3.end());
    temp.insert(temp.end(), r4.begin(), r4.end());
    return temp;
}
vector<Rectangle *> QuadTree::getInBoxes(Node *n, Function *F, double cutoff)
{
    vector<Rectangle *> temp;
    if (n->isLeaf())
    {
        double integral = n->integrate(F);
        if (integral != -1)
        {
            if (integral < -scaleCutoff(cutoff, n->getLevel()))
            {
                temp.push_back(n->getRekt());
                return temp;
            }
        }
    }
    vector<Node *> children = n->getChildren();
    vector<Rectangle *> r1 = getInBoxes(children[0], F, cutoff);
    vector<Rectangle *> r2 = getInBoxes(children[1], F, cutoff);
    vector<Rectangle *> r3 = getInBoxes(children[2], F, cutoff);
    vector<Rectangle *> r4 = getInBoxes(children[3], F, cutoff);
    temp.insert(temp.end(), r1.begin(), r1.end());
    temp.insert(temp.end(), r2.begin(), r2.end());
    temp.insert(temp.end(), r3.begin(), r3.end());
    temp.insert(temp.end(), r4.begin(), r4.end());
    return temp;
}

//first box is outbox second is in box
twoVects *QuadTree::getAllBoxes(Node *n, Function *F, double cutoff)
{
    vector<Rectangle *> temp1;
    vector<Rectangle *> temp2;
    twoVects *temp = new twoVects(temp1, temp2);

    if (n->isLeaf())
    {
        double integral = n->getRekt()->approx(F);
        if (integral < -scaleCutoff(cutoff, n->getLevel()))
        {
            //inboxes
            temp2.push_back(n->getRekt());
        }
        else if (integral > scaleCutoff(cutoff, n->getLevel()))
        {
            //outboxes
            temp1.push_back(n->getRekt());
        }
        temp->setV1(temp1);
        temp->setV2(temp2);
        return temp;
    }
    vector<Node *> children = n->getChildren();
    twoVects *r1 = getAllBoxes(children[0], F, cutoff);
    twoVects *r2 = getAllBoxes(children[1], F, cutoff);
    twoVects *r3 = getAllBoxes(children[2], F, cutoff);
    twoVects *r4 = getAllBoxes(children[3], F, cutoff);

    temp->append(r1);
    temp->append(r2);
    temp->append(r3);
    temp->append(r4);

    return temp;
}

void QuadTree::draw(sf::RenderWindow *window)
{
    QuadTree::drawRoot(root, window);
}

void QuadTree::drawRoot(Node *n, sf::RenderWindow *window)
{
    if (n->isLeaf())
    {
        n->getRekt()->draw(window);
        return;
    }
    else
    {
        vector<Node *> children = n->getChildren();
        drawRoot(children[0], window);
        drawRoot(children[1], window);
        drawRoot(children[2], window);
        drawRoot(children[3], window);
    }
}

void QuadTree::divideTreeNTimes(double minX, double maxX, double minY, double maxY, Node *n, int level)
{
    if (level == 0)
    {
        n->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        return;
    }
    else
    {
        n->createChildren();
        vector<Node *> temp = n->getChildren();
        temp[0]->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        temp[1]->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        temp[2]->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        temp[3]->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        vector<Node *> children = n->getChildren();
        divideTreeNTimes(minX, maxX, minY, maxY, children[0], level - 1);
        divideTreeNTimes(minX, maxX, minY, maxY, children[1], level - 1);
        divideTreeNTimes(minX, maxX, minY, maxY, children[2], level - 1);
        divideTreeNTimes(minX, maxX, minY, maxY, children[3], level - 1);
    }
}

void QuadTree::divideCompMid(double minX, double maxX, double minY, double maxY, Node *n, Function *F, double tol, int maximumLevel)
{
    vector<Node *> fakeChildren = n->createFakeChildren();
    double sum=0;
    for(int i=0;i<fakeChildren.size();i++)
    {
        sum+=abs(fakeChildren[i]->getRekt()->approx(F));
    }
    double temp=fakeChildren[0]->getRekt()->approx(F);
    if (abs(sum-abs(n->getRekt()->approx(F))) > tol && n->getLevel() < maximumLevel)
    {
        n->createChildren(fakeChildren);
        divideCompMid(minX, maxX, minY, maxY, fakeChildren[0], F, tol, maximumLevel);
        divideCompMid(minX, maxX, minY, maxY, fakeChildren[1], F, tol, maximumLevel);
        divideCompMid(minX, maxX, minY, maxY, fakeChildren[2], F, tol, maximumLevel);
        divideCompMid(minX, maxX, minY, maxY, fakeChildren[3], F, tol, maximumLevel);
    }
    else
    {
        n->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        return;
    }
}

double QuadTree::scaleCutoff(double cutoff, int level)
{
    return cutoff / pow(4, level);
}

vector<double> QuadTree::getDifArray(Node *n, Function *F, double cutoff)
{
    vector<double> temp;
    if (n->isLeaf())
    {
        double integral = n->getRekt()->approx(F);
        if (abs(integral) > abs(scaleCutoff(cutoff, n->getLevel())))
            temp.push_back(integral);
        return temp;
    }
    else
    {
        vector<Node *> children = n->getChildren();
        vector<double> r1 = getDifArray(children[0], F, cutoff);
        vector<double> r2 = getDifArray(children[1], F, cutoff);
        vector<double> r3 = getDifArray(children[2], F, cutoff);
        vector<double> r4 = getDifArray(children[3], F, cutoff);
        temp.insert(temp.end(), r1.begin(), r1.end());
        temp.insert(temp.end(), r2.begin(), r2.end());
        temp.insert(temp.end(), r3.begin(), r3.end());
        temp.insert(temp.end(), r4.begin(), r4.end());
    }
    return temp;
}
tripleVect *QuadTree::getAllRelevantVects(Node *n, Function *F, double cutoff)
{
    vector<Rectangle *> temp1;
    vector<Rectangle *> temp2;

    vector<double> supply;
    vector<double> demand;
    twoVects *t1 = new twoVects(temp1, temp2);
    twoVectsDoub *t2 = new twoVectsDoub(supply, demand);
    tripleVect *temp = new tripleVect(t1, t2);
    if (n->isLeaf())
    {
        double integral = n->getRekt()->approx(F);
        if (integral < -abs(scaleCutoff(cutoff, n->getLevel())))
        {
            //inboxes
            t1->v2.push_back(n->getRekt());
            n->getRekt()->setColor("inbox");
            //demand
            t2->v2.push_back(integral);
        }
        else if (integral > scaleCutoff(cutoff, n->getLevel()))
        {
            //outboxes
            t1->v1.push_back(n->getRekt());
            //supply
            n->getRekt()->setColor("outbox");
            t2->v1.push_back(integral);
        }
        temp->setDoub(t2);
        temp->setRect(t1);
        return temp;
    }
    vector<Node *> children = n->getChildren();
    tripleVect *r1 = getAllRelevantVects(children[0], F, cutoff);
    tripleVect *r2 = getAllRelevantVects(children[1], F, cutoff);
    tripleVect *r3 = getAllRelevantVects(children[2], F, cutoff);
    tripleVect *r4 = getAllRelevantVects(children[3], F, cutoff);

    temp->append(r1);
    temp->append(r2);
    temp->append(r3);
    temp->append(r4);

    return temp;
}

double QuadTree::normalize(Node *n, Function *F)
{
    double temp = 0;
    if (n->isLeaf())
    {
        temp += n->getRekt()->approx(F);
    }
    else
    {
        vector<Node *> children = n->getChildren();
        double t1 = normalize(children[0], F);
        double t2 = normalize(children[0], F);
        double t3 = normalize(children[0], F);
        double t4 = normalize(children[0], F);
        temp += t1;
        temp += t2;
        temp += t3;
        temp += t4;
    }
    return temp;
}

void QuadTree::divideCompMidAcc(double minX, double maxX, double minY, double maxY, Node *n, Function *F, double tol, int maximumLevel, int accuracy)
{
    vector<Node *> fakeChildren = n->createFakeChildren();
    if (abs(fakeChildren[0]->getRekt()->approx(F) - n->getRekt()->approx(F)) > tol)
    {
        n->createChildren(fakeChildren);
        divideCompMid(minX, maxX, minY, maxY, fakeChildren[0], F, tol, maximumLevel);
        divideCompMid(minX, maxX, minY, maxY, fakeChildren[1], F, tol, maximumLevel);
        divideCompMid(minX, maxX, minY, maxY, fakeChildren[2], F, tol, maximumLevel);
        divideCompMid(minX, maxX, minY, maxY, fakeChildren[3], F, tol, maximumLevel);
    }
    else
    {
        n->getRekt()->createSfRectFromCartesian(minX, maxX, minY, maxY);
        return;
    }
}

tripleVect *QuadTree::getAllRelevantVectsAcc(Node *n, Function *F, double cutoff, int accuracy, int cutoffAcc)
{
    vector<Rectangle *> temp1;
    vector<Rectangle *> temp2;

    vector<double> supply;
    vector<double> demand;
    twoVects *t1 = new twoVects(temp1, temp2);
    twoVectsDoub *t2 = new twoVectsDoub(supply, demand);
    tripleVect *temp = new tripleVect(t1, t2);
    if (n->isLeaf())
    {
        double integral = n->getRekt()->getAccurateApprox(F, cutoffAcc);
        if (integral < -(scaleCutoff(cutoff, n->getLevel())))
        {
            integral = n->getRekt()->getAccurateApprox(F, accuracy);
            // cout<<"inbox: "<<integral<<endl;
            //inboxes
            t1->v2.push_back(n->getRekt());
            //demand
            n->getRekt()->setColor("inbox");
            t2->v2.push_back(integral);
        }
        else if (integral > scaleCutoff(cutoff, n->getLevel()))
        {
            integral = n->getRekt()->getAccurateApprox(F, accuracy);
            // cout<<"outbox: "<<integral<<endl;
            //outboxes
            t1->v1.push_back(n->getRekt());
            //supply
            n->getRekt()->setColor("outbox");
            t2->v1.push_back(integral);
        }
        temp->setDoub(t2);
        temp->setRect(t1);
        return temp;
    }
    vector<Node *> children = n->getChildren();
    tripleVect *r1 = getAllRelevantVectsAcc(children[0], F, cutoff, accuracy, cutoffAcc);
    tripleVect *r2 = getAllRelevantVectsAcc(children[1], F, cutoff, accuracy, cutoffAcc);
    tripleVect *r3 = getAllRelevantVectsAcc(children[2], F, cutoff, accuracy, cutoffAcc);
    tripleVect *r4 = getAllRelevantVectsAcc(children[3], F, cutoff, accuracy, cutoffAcc);

    temp->append(r1);
    temp->append(r2);
    temp->append(r3);
    temp->append(r4);
    return temp;
}

double QuadTree::normalizeAcc(Node *n, Function *F, int accuracy)
{
    double temp = 0;
    if (n->isLeaf())
    {
        temp += n->getRekt()->getAccurateApprox(F, accuracy);
    }
    else
    {
        vector<Node *> children = n->getChildren();
        double t1 = normalizeAcc(children[0], F, accuracy);
        double t2 = normalizeAcc(children[0], F, accuracy);
        double t3 = normalizeAcc(children[0], F, accuracy);
        double t4 = normalizeAcc(children[0], F, accuracy);
        temp += t1;
        temp += t2;
        temp += t3;
        temp += t4;
    }
    return temp;
}

tripleVect *QuadTree::getAllRelevantVectsGaussQuad(Node *n, Function *F, double cutoff, int MAX_ITERATIONS, GaussianQuadrature *gaussQuad)
{
    //std::cout<<cutoff<<std::endl;
    vector<Rectangle *> temp1;
    vector<Rectangle *> temp2;

    vector<double> supply;
    vector<double> demand;
    twoVects *t1 = new twoVects(temp1, temp2);
    twoVectsDoub *t2 = new twoVectsDoub(supply, demand);
    tripleVect *temp = new tripleVect(t1, t2);
    if (n->isLeaf())
    {

        double integral = n->getRekt()->integralGaussApprox(MAX_ITERATIONS, F, gaussQuad);
        //cout << "integral: " << integral << endl;
        if (integral < -(scaleCutoff(cutoff, n->getLevel())))
        {
            t1->v2.push_back(n->getRekt());
            n->getRekt()->setColor("inbox");
            t2->v2.push_back(integral);
        }
        else if (integral > scaleCutoff(cutoff, n->getLevel()))
        {
            t1->v1.push_back(n->getRekt());
            n->getRekt()->setColor("outbox");
            t2->v1.push_back(integral);
        }
        temp->setDoub(t2);
        temp->setRect(t1);
        return temp;
    }
    vector<Node *> children = n->getChildren();
    tripleVect *r1 = getAllRelevantVectsGaussQuad(children[0], F, cutoff, MAX_ITERATIONS, gaussQuad);
    tripleVect *r2 = getAllRelevantVectsGaussQuad(children[1], F, cutoff, MAX_ITERATIONS, gaussQuad);
    tripleVect *r3 = getAllRelevantVectsGaussQuad(children[2], F, cutoff, MAX_ITERATIONS, gaussQuad);
    tripleVect *r4 = getAllRelevantVectsGaussQuad(children[3], F, cutoff, MAX_ITERATIONS, gaussQuad);

    temp->append(r1);
    temp->append(r2);
    temp->append(r3);
    temp->append(r4);
    return temp;
}

vector<std::string> QuadTree::getStringCoordOfAllCells(Node *n)
{
    vector<std::string> temp;

    if (n->isLeaf())
    {
        temp.push_back(n->getRekt()->toStringCoordTopLeft());
        temp.push_back(n->getRekt()->toStringCoordBottomRight());
        //std::cout<<n->getRekt()->toStringCoordTopLeft()<<std::endl;
        return temp;
    }
    vector<Node *> children = n->getChildren();
    vector<std::string> r1 = getStringCoordOfAllCells(children[0]);
    vector<std::string> r2 = getStringCoordOfAllCells(children[1]);
    vector<std::string> r3 = getStringCoordOfAllCells(children[2]);
    vector<std::string> r4 = getStringCoordOfAllCells(children[3]);
    temp.insert(temp.end(), r1.begin(), r1.end());
    temp.insert(temp.end(), r2.begin(), r2.end());
    temp.insert(temp.end(), r3.begin(), r3.end());
    temp.insert(temp.end(), r4.begin(), r4.end());
    return temp;
    /*

void twoVectsDoub::appendToV1(std::vector<double> t)
{
    v1.insert(v1.end(), t.begin(), t.end());
}
    */
}
