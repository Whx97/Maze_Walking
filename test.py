import torch
import matplotlib.pyplot as plt
import numpy as np
if __name__ == '__main__':
    print('hello python')
    # print(torch.ones(3))
    x = np.random.rand(100)
    y = np.cos(x)
    plt.plot(x,y)
    plt.show()

def sps_block_diag(tensors):
    idx_list = []
    elem_list = []
    start_idx = torch.zeros(2).long().to(tensors[0].device)
    for i, t in enumerate(tensors):
        print(i, t, t._indices())
    for i, t in enumerate(tensors):
        print(i, t, t._indices())
        # expand_as  
        print(start_idx.unsqueeze(1))        
        print(start_idx.unsqueeze(1).expand_as(t._indices()))        
        idx_list.append(t._indices() + start_idx.unsqueeze(1).expand_as(t._indices()))
        elem_list.append(t._values())
        start_idx += torch.tensor(t.shape).to(t.device)
    block_idx = torch.cat(idx_list, 1)
    block_elem = torch.cat(elem_list)
    block = torch.sparse.FloatTensor(block_idx, block_elem, torch.Size(start_idx))
    return block


i = torch.LongTensor([[ 0,  0,  1,  8,  8,  2,  2,  3,  6,  6,  4,  9,  9,  1,
                         8,  2,  7,  9,  3,  6,  4,  5,  7,  5, 10, 11],
                       [ 1,  8,  2,  7,  9,  3,  6,  4,  5,  7,  5, 10, 11,  0,
                         0,  1,  8,  8,  2,  2,  3,  6,  6,  4,  9,  9]])
v = torch.FloatTensor([1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.,
                      1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1., 1.])
# i = torch.LongTensor([[0, 1, 2],
#                     [0, 0, 1]])
# v = torch.FloatTensor([1, 1, 3])
# print(torch.sparse.FloatTensor(i, v, torch.Size([3,3])).to_dense())
# print(torch.zeros(2))
t = torch.sparse.FloatTensor(i, v, torch.Size([12, 12]))
# tens = torch.tensor([1,2,3])
print(sps_block_diag([t]).to_dense())
