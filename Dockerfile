FROM nvidia/cuda:11.0-devel-centos7 AS base
MAINTAINER lpizarrobaeza@gmail.com

RUN yum update -y && yum install -y epel-release && yum install -y git cmake yaml-cpp03 yaml-cpp03-devel glog glog-devel gflags gflags-devel cmake freeglut-devel freeglut libXmu-devel libXi-devel && yum autoremove -y && yum clean all
RUN git clone --depth 1 https://github.com/LeoXDXp/CUDA---Shallow-water-equations.git /mnt && cd /mnt/bin/ && cmake .. && make -j4

FROM nvidia/cuda:11.0-runtime-centos7
COPY --from=base /mnt/bin/swegpu /usr/local/bin/
COPY --from=base /mnt/res/*.yaml /tmp/
WORKDIR /tmp
RUN useradd -M app
RUN chown -R app:app /tmp/
USER app
CMD swegpu tsunami.yaml -roty 225 -rotx 15 -zoom 15 -wspf 20 -kernelflops 256
