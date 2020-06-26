package com.gildedrose;

class GildedRose {
    Item[] items;

    public static final String AGED_BRIE = "Aged Brie";
    public static final String BACKSTAGE = "Backstage passes to a TAFKAL80ETC concert";
    public static final String SULFURAS  = "Sulfuras, Hand of Ragnaros";
    public static final String CONJURED  = "Conjured Mana Cake";

    public GildedRose(Item[] items) {
        this.items = items;
    }

    public void updateQuality() {
    //public void newUpdateQuality() {
        for (Item currentItem : items) {
            int decreaseAmount = (currentItem.sellIn > 0) ? 1 : 2;

            switch (currentItem.name) {
                case AGED_BRIE:
                    // Increase instead of decrease.
                    currentItem.quality += decreaseAmount;
                    break;

                case BACKSTAGE:
                    if (currentItem.sellIn > 10) {
                        currentItem.quality++;
                    } else if (currentItem.sellIn <= 10 && currentItem.sellIn > 5 ) {
                        currentItem.quality += 2;
                    } else if (currentItem.sellIn <= 5 && currentItem.sellIn > 0) {
                        currentItem.quality += 3;
                    } else {  // sellIn <= 0
                        currentItem.quality = 0;
                    }
                    break;

                case SULFURAS:
                    break;

                case CONJURED:
                    currentItem.quality -= decreaseAmount * 2;
                    break;

                default:
                    currentItem.quality -= decreaseAmount;
            }

            // `sellIn` decreases for every item except `Sulfuras`.
            if (!currentItem.name.equals(SULFURAS)) {
                currentItem.sellIn--;
            }

            // Quality is never less than 0 and quality cant be over 50 unless
            // this is SULFURAS.
            if (currentItem.quality < 0) {
                currentItem.quality = 0;
            } else if (currentItem.quality > 50 && !currentItem.name.equals(SULFURAS)) {
                currentItem.quality = 50;
            }
        }
    }

    //public void updateQuality() {
    public void oldUpdateQuality() {
        for (int i = 0; i < items.length; i++) {
            if (!items[i].name.equals("Aged Brie")
                    && !items[i].name.equals("Backstage passes to a TAFKAL80ETC concert")) {
                if (items[i].quality > 0) {
                    if (!items[i].name.equals("Sulfuras, Hand of Ragnaros")) {
                        items[i].quality = items[i].quality - 1;
                    }
                }
            } else {
                if (items[i].quality < 50) {
                    items[i].quality = items[i].quality + 1;

                    if (items[i].name.equals("Backstage passes to a TAFKAL80ETC concert")) {
                        if (items[i].sellIn < 11) {
                            if (items[i].quality < 50) {
                                items[i].quality = items[i].quality + 1;
                            }
                        }

                        if (items[i].sellIn < 6) {
                            if (items[i].quality < 50) {
                                items[i].quality = items[i].quality + 1;
                            }
                        }
                    }
                }
            }

            if (!items[i].name.equals("Sulfuras, Hand of Ragnaros")) {
                items[i].sellIn = items[i].sellIn - 1;
            }

            if (items[i].sellIn < 0) {
                if (!items[i].name.equals("Aged Brie")) {
                    if (!items[i].name.equals("Backstage passes to a TAFKAL80ETC concert")) {
                        if (items[i].quality > 0) {
                            if (!items[i].name.equals("Sulfuras, Hand of Ragnaros")) {
                                items[i].quality = items[i].quality - 1;
                            }
                        }
                    } else {
                        items[i].quality = items[i].quality - items[i].quality;
                    }
                } else {
                    if (items[i].quality < 50) {
                        items[i].quality = items[i].quality + 1;
                    }
                }
            }
        }
    }

}