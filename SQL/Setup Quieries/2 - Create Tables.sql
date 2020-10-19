CREATE TABLE `tempuraturedata`.`tempurature` (
  `SensorId` VARCHAR(50) NOT NULL,
  `Timestamp` DATETIME NOT NULL,
  `Tempurature` DECIMAL(6,4) NOT NULL,
  INDEX `idx_Tempurature_SensorId` (`SensorId` ASC) VISIBLE,
  INDEX `idx_Tempurature_Timestamp` (`Timestamp` ASC) VISIBLE);