#include <bits/stdc++.h>

using namespace std;

int numbVideo, numbEndpoint, numbRequest, numbCache, sizeCache;

vector<int>videoSizes;

struct Endpoint
{
    int latency, _numbCache;
    int cacheLatency[1000] = {0};
};

vector<Endpoint> endpointsArr;

struct Request
{
    int _numbRequest, videoID, endpointID;
};

vector<Request> requestsArr;

struct Cache
{
    vector<int> videos;
    int getCrtSize();
};

int Cache::getCrtSize()
{
    int sz = 0;
    for(int i = 0; i < videos.size(); i++)
        sz += videoSizes[videos[i]];
    return sz;
}

vector<Cache> cachesArr;

void readData(const char *file_name)
{
    fstream fin (file_name);

    fin >> numbVideo >> numbEndpoint >> numbRequest >> numbCache >> sizeCache;

    for (int i = 0; i < numbVideo; ++i)
    {
        int x;
        fin >> x;
        videoSizes.push_back(x);
    }

    for (int i = 0; i < numbEndpoint; ++i)
    {
        Endpoint endp;
        fin >> endp.latency >> endp._numbCache;

        for(int j = 0; j < endp._numbCache; ++j)
        {
            int ID;
            fin >> ID;
            fin >> endp.cacheLatency[ID];
        }

        endpointsArr.push_back(endp);
    }

    cachesArr.resize(numbCache);

    for(int i = 0; i < numbRequest; ++i)
    {
        Request req;
        fin >> req.videoID >> req.endpointID >> req._numbRequest;
        requestsArr.push_back(req);
    }
}

void solve2_0()
{
    int i = 0;
    while(requestsArr.size() > 0)
    {
        cout<<++i<<endl;
        int maxScore = -1;
        int reqId = -1;
        for(int i = 0; i < requestsArr.size(); i++)
        {
            int score = requestsArr[i]._numbRequest * endpointsArr[requestsArr[i].endpointID].latency;

            if(score > maxScore)
            {
                maxScore = score;
                reqId = i;
            }
        }

        // pana aici am cea mai costisitoare cerere
        // adica, reqId

        // caut un cache bun pentru requestsArr[reqId].endpointID;

        Endpoint& crtEnd = endpointsArr[requestsArr[reqId].endpointID];

        int bestLatency = 0x7fffffff;
        int bestLatencyId = -1;

        for(int i = 0; i < 1000; i++)
        {
            if(crtEnd.cacheLatency[i] != 0 && crtEnd.cacheLatency[i] < bestLatency &&
               cachesArr[i].getCrtSize() + videoSizes[requestsArr[reqId].videoID] <= sizeCache )
            {
                bestLatency = crtEnd.cacheLatency[i];
                bestLatencyId = i;
            }
        }

        // pana aici am cel mai bun cache, sper

        // cout<<bestLatencyId<<endl;

        if(bestLatencyId != -1)
        {
            bool ok = true;
            for(int i = 0; i < cachesArr[bestLatencyId].videos.size(); i++)
            {
                if(cachesArr[bestLatencyId].videos[i] == requestsArr[reqId].videoID)
                {
                    ok = false;
                    break;
                }
            }
            if(ok)
            {
                cachesArr[bestLatencyId].videos.push_back(requestsArr[reqId].videoID);
            }
        }

        // cout<<reqId<<endl;
        requestsArr.erase(requestsArr.begin() + reqId);
    }
}

void afisare(char* fileName)
{
    ofstream fout(fileName);

    int nr = 0;
    for(int i = 0; i < cachesArr.size(); i++)
    {
        if(cachesArr[i].videos.size() > 0)
            nr++;
    }

    fout<<nr<<endl;
    for(int i = 0; i < cachesArr.size(); i++)
    {
        if(cachesArr[i].videos.size() > 0)
        {
            fout<<i<<" ";
            for(int j = 0; j < cachesArr[i].videos.size(); j++)
                fout<<cachesArr[i].videos[j]<<" ";
            fout<<'\n';
        }
    }

    fout.close();
}

int main(int argc, char *argv[])
{
    readData(argv[1]);

    solve2_0();

    cout<<"rezolvat\n";
//
//    cout<<cachesArr[0].getCrtSize();
//
//    cachesArr[0].videos.push_back(videoSizes[31]);
//
//    cout<<cachesArr[0].getCrtSize();

    afisare(argv[2]);
//
//    cout<<cachesArr.size();
//
//    cout<<endl;
//
//    for(int i = 0; i < cachesArr.size(); i++)
//    {
//        cout<<i<<": ";
//        for(int j = 0; j < cachesArr[i].videos.size(); j++)
//            cout<<cachesArr[i].videos[j]<<" ";
//        cout<<endl;
//    }

    return 0;
}

