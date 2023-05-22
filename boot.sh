set -eu
# kvm \
qemu-system-x86_64 \
  -kernel arch/x86_64/boot/bzImage \
  -hda ../buildroot/output/images/rootfs.ext4 \
  -append "root=/dev/sda rw console=ttyS0,115200 cgroup_no_v1=all systemd.unified_cgroup_hierarchy=1 kgdboc=ttyS0,115200 nokaslr" \
  -nographic \
  -no-reboot \
  -enable-kvm \
  -cpu host \
  -smp $1 \
  -s \
  -m 1024M
