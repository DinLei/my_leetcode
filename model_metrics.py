def auc(actual, pred):
    assert (len(actual) == len(pred))
    eval_map = list(zip(pred, actual))
    rank = [a for p, a in sorted(eval_map, key=lambda x: x[0])]     # 样本 真实值 按 相应预估值由小到大 排序
    rank_list = [i for i in range(len(rank)) if rank[i] == 1]       # 正样本所在的索引：正样本预测值超过其他所有的样本的数目

    pos_num = np.sum(actual)
    neg_num = len(actual) - pos_num

    # 假设M个正样本
    # 第一大的正样本与M-1个正样本比较过
    # 第二大的正样本与M-2个正样本比较过
    # ......
    # 等差序列求和：M*(M-1)/2
    auc_val = (sum(rank_list) - (pos_num * (pos_num - 1)) / 2) / (pos_num * neg_num)
    return auc_val