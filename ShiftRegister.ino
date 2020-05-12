boolean isBitSet(byte patroon, int index) {
  byte check = B00000001 << index;
  return ((patroon & check) == check);
}
