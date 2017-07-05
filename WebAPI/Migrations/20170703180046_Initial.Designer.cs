using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Infrastructure;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;
using WorkCounter.Data;

namespace WorkCounter.Migrations
{
    [DbContext(typeof(DataContext))]
    [Migration("20170703180046_Initial")]
    partial class Initial
    {
        protected override void BuildTargetModel(ModelBuilder modelBuilder)
        {
            modelBuilder
                .HasAnnotation("ProductVersion", "1.1.2");

            modelBuilder.Entity("WorkCounter.Data.Models.Device", b =>
                {
                    b.Property<long>("ID")
                        .ValueGeneratedOnAdd();

                    b.Property<DateTime?>("DateDeleted");

                    b.Property<string>("Name");

                    b.HasKey("ID");

                    b.ToTable("Device");
                });

            modelBuilder.Entity("WorkCounter.Data.Models.Pass", b =>
                {
                    b.Property<long>("ID")
                        .ValueGeneratedOnAdd();

                    b.Property<DateTime?>("DateDeleted");

                    b.Property<DateTime>("DateTimeAdded");

                    b.Property<long?>("DeviceID");

                    b.Property<int>("Distance");

                    b.Property<long>("Millis");

                    b.HasKey("ID");

                    b.HasIndex("DeviceID");

                    b.ToTable("Pass");
                });

            modelBuilder.Entity("WorkCounter.Data.Models.Pass", b =>
                {
                    b.HasOne("WorkCounter.Data.Models.Device", "Device")
                        .WithMany()
                        .HasForeignKey("DeviceID");
                });
        }
    }
}
