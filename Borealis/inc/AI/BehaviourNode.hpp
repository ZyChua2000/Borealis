#pragma once

enum class NodeStatus
{
    READY, // node is enterable
    RUNNING, // node is currently running
    EXITING, // node has succeeded or failed
    SUSPENDED // node won't exceute anything
};

enum class NodeResult
{
    IN_PROGRESS, // still being run 
    SUCCESS, // node succeeded
    FAILURE // node failed
};

class  BehaviourNode
{
public:
    BehaviourNode();
    ~BehaviourNode();
        
    // readability status getters
    bool is_ready() const;
    bool succeeded() const;
    bool failed() const;
    bool is_running() const;
    bool is_suspended() const;

    // set just this node's status
    void set_status(NodeStatus newStatus);

    // set this node and all childrens' status, recursively
    void set_status_all(NodeStatus newStatus);

    // set only the direct children's status
    void set_status_children(NodeStatus newStatus);

    void set_result(NodeResult result);

    void set_result_children(NodeResult result);

    NodeStatus get_status() const;

    NodeResult get_result() const;

    void tick(float dt);

    const char* get_name() const;
    //const char* get_summary() const;

    virtual BehaviourNode* clone() = 0;

protected:
    void on_leaf_enter();

    // override for any non-generic logic
    virtual void on_enter();
    virtual void on_update(float dt);
    virtual void on_exit();

    // convenience functions for setting status and result
    void on_success();
    void on_failure();

private:
    const char* name;

};

// CRTP base class with unique_ptr
template <typename T>
class BaseNode : public BehaviourNode {
public:
    virtual std::unique_ptr<BehaviourNode> clone() 
    {
        return std::make_unique<T>(*static_cast<T*>(this));  // Return unique_ptr clone
    }
};